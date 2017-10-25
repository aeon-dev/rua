#include "assembler.h"
#include <aeon/streams/file_stream.h>
#include <aeon/common/string.h>
#include <aeon/utility/timer.h>
#include <array>
#include <iostream>
#include <stdexcept>
#include <iomanip>

namespace rua
{

static const auto instruction_bits = 8;

// AT28C16
static const auto eeprom_address_bits = 11;

static const auto max_cycles_per_opcode = (1 << (eeprom_address_bits - instruction_bits));

static const std::string firmware_filename = "firmware";
static const std::string firmware_extension = "bin";

assembler::assembler()
    : input_file_()
    , signals_parser_(std::make_unique<rua::control_signals_parser>("signals.txt"))
    , opcode_()
    , macros_()
    , last_header_()
{
}

bool assembler::parse_arguments(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage:\n"
                  << "mcasm input_file\n";
        return false;
    }

    input_file_ = argv[1];

    return true;
}

void assembler::assemble()
{
    parse();
    write_output_roms();
    std::cout << "Done.\n";
}

void assembler::parse()
{
    aeon::utility::timer timer;
    std::cout << "Assembling...";
    parse_file(input_file_);

    auto milliseconds = static_cast<float>(timer.get_time_difference() * 1000);

    std::cout << "done. (Took: " << std::setw(3) << std::setprecision(2) << milliseconds << "ms.)\n";
}

void assembler::parse_file(const std::string &file)
{
    auto signals = signals_parser_->get_control_signals();

    aeon::streams::file_stream s(file, aeon::streams::file_mode::text);

    // int current_opcode = -1;
    unsigned int line_number = 0;

    while (!s.eof())
    {
        ++line_number;

        auto line = aeon::common::string::trimmed(s.read_line());

        if (line.empty())
            continue;

        if (line[0] == '#')
        {
            parse_include(line, line_number);
            continue;
        }

        // Strip comments at the end of the line.
        auto split_result = aeon::common::string::split(line, '#');
        line = aeon::common::string::trimmed(split_result[0]);

        if (line[0] == '!')
        {
            parse_macro_call(line, line_number);
            continue;
        }

        // New header (macro or opcode)
        if (line[0] == '[')
        {
            last_header_ = header(line, line_number);

            if (last_header_.get_type() == header_type::macro)
                macros_[last_header_.get_name()] = {};

            continue;
        }

        parse_instructions(line, line_number);
    }
}

void assembler::parse_include(const std::string &line, int line_number)
{
    if (!aeon::common::string::begins_with(line, "#include"))
        return;

    auto begin = line.find_first_of('"');
    auto end = line.find_last_of('"');

    if (begin == std::string::npos || end == std::string::npos)
    {
        throw std::runtime_error("Error (line " + std::to_string(line_number) +
                                 "): Could not parse #include directive.");
    }

    auto filename = aeon::common::string::strip_both(line.substr(begin, end), 1);
    parse_file(filename);
}

void assembler::parse_macro_call(const std::string &line, int line_number)
{
    if (last_header_.get_type() == header_type::none)
        throw std::runtime_error("Error (line " + std::to_string(line_number) +
                                 "): Unexpected instructions. Expected header instead.");

    auto macro_name = aeon::common::string::strip_left(line, 1);

    auto result = macros_.find(macro_name);

    if (result == macros_.end())
    {
        throw std::runtime_error("Error (line " + std::to_string(line_number) + "): Undefined macro: '" + macro_name +
                                 "'");
    }

    if (last_header_.get_type() == header_type::macro)
    {
        if (last_header_.get_name() == macro_name)
            throw std::runtime_error("Error (line " + std::to_string(line_number) +
                                     "): Infinite recursion detected! A macro can not call itself.");

        for (auto opcode : result->second)
        {
            macros_[last_header_.get_name()].push_back(opcode);
        }
    }
    else
    {
        for (auto opcode : result->second)
        {
            opcode_[last_header_.get_opcode()].push_back(opcode);
            check_opcode_length(line_number);
        }
    }
}

void assembler::parse_instructions(const std::string &line, int line_number)
{
    if (last_header_.get_type() == header_type::none)
        throw std::runtime_error("Error (line " + std::to_string(line_number) +
                                 "): Unexpected instructions. Expected header instead.");

    auto instructions = aeon::common::string::split(line, ',');

    std::uint64_t microcode = 0;

    try
    {
        for (auto &instruction : instructions)
        {
            auto signal = signals_parser_->get_control_signal(aeon::common::string::trimmed(instruction));
            microcode |= signal.bit_value;
        }
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error (line " + std::to_string(line_number) + "): " + e.what());
    }

    if (last_header_.get_type() == header_type::macro)
    {
        macros_[last_header_.get_name()].push_back(microcode);
    }
    else
    {
        opcode_[last_header_.get_opcode()].push_back(microcode);
        check_opcode_length(line_number);
    }
}

void assembler::check_opcode_length(const int line_number) const
{
    if (opcode_.at(last_header_.get_opcode()).size() > max_cycles_per_opcode)
        throw std::runtime_error("Error (line " + std::to_string(line_number) +
                                 "): Instruction too long. Maximum cycles per instruction: " +
                                 std::to_string(max_cycles_per_opcode));
}

void assembler::write_output_roms()
{
    aeon::utility::timer timer;

    std::cout << "Writing ROM firmware...";

    const auto array_size = (eeprom_address_bits << 8);

    for (int i = 0; i < 8; ++i)
    {
        std::array<std::uint8_t, array_size> firmware;
        memset(firmware.data(), 0, array_size);

        for (const auto &opcode_pair : opcode_)
        {
            const auto opcode = static_cast<int>(opcode_pair.first);
            const auto &microcodes = opcode_pair.second;

            int cycle = 0;
            for (auto microcode : microcodes)
            {
                const unsigned char *microcode_byte = reinterpret_cast<unsigned char *>(&microcode);
                firmware[opcode + ((cycle) << 8)] = microcode_byte[i];
                ++cycle;
            }
        }

        auto filename = firmware_filename + std::to_string(i) + "." + firmware_extension;

        aeon::streams::file_stream rom(filename,
                                       aeon::streams::access_mode::write | aeon::streams::access_mode::truncate);
        rom.write(firmware.data(), array_size);
    }

    auto milliseconds = static_cast<float>(timer.get_time_difference() * 1000);
    std::cout << "done. (Took: " << std::setw(3) << std::setprecision(2) << milliseconds << "ms.)\n";
}

} // namespace rua
