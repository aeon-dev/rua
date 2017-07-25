#include "control_signals.h"
#include <iostream>
#include <aeon/common/string.h>
#include <sstream>
#include <stdexcept>

namespace rua
{

control_signals_parser::control_signals_parser(const std::string &signals_path)
    : file_(signals_path, aeon::streams::file_mode::text)
    , control_signals_()
{
    parse_control_lines();
}

auto control_signals_parser::get_control_signals() const -> std::vector<control_signal>
{
    return control_signals_;
}

auto control_signals_parser::get_control_signal(const std::string &name) const -> control_signal
{
    auto upper_name = aeon::common::string::to_upper(name);

    for (auto &signal : control_signals_)
    {
        if (signal.mnemonic == upper_name)
            return signal;
    }

    throw std::runtime_error("Could not find control signal mnemonic: " + upper_name);
}

void control_signals_parser::parse_control_lines()
{
    auto line_number = 1u;
    while (!file_.eof())
    {
        auto line = aeon::common::string::trimmed(file_.read_line());

        if (line.empty())
            continue;

        if (line[0] == '#')
            continue;

        parse_line(line, line_number++);
    }
}

void control_signals_parser::parse_line(const std::string &line, const unsigned int line_number)
{
    auto microcode_entry = aeon::common::string::split(line, ',');

    if (microcode_entry.size() != 3)
        throw std::runtime_error("Error (line " + std::to_string(line_number) +
                                 "): Expected 3 tokens per line seperated by a comma.");

    auto signal_name = parse_signal_name(microcode_entry, line_number);
    auto signal_bitval = parse_signal_bitval(microcode_entry, line_number);
    auto signal_description = parse_signal_description(microcode_entry, line_number);

    control_signals_.push_back({signal_name, signal_description, signal_bitval});
}

auto control_signals_parser::parse_signal_name(const std::vector<std::string> &line,
                                               const unsigned int line_number) const -> std::string
{
    auto signal_name = aeon::common::string::trimmed(line[0]);

    if (signal_name.empty())
        throw std::runtime_error("Error (line " + std::to_string(line_number) + "): Expected signal name.");

    return aeon::common::string::to_upper(signal_name);
}

auto control_signals_parser::parse_signal_bitval(const std::vector<std::string> &line, const unsigned line_number) const
    -> std::uint64_t
{
    auto signal_bitval_str = aeon::common::string::trimmed(line[1]);

    if (signal_bitval_str.size() <= 3) // Expect at least 0x0
        throw std::runtime_error("Error (line " + std::to_string(line_number) +
                                 "): Expected signal bit value in hex. Like: 0x0.");

    if (signal_bitval_str[0] != '0' || signal_bitval_str[1] != 'x')
        throw std::runtime_error("Error (line " + std::to_string(line_number) +
                                 "): Expected signal bit value in hex. Like: 0x0.");

    auto bitval = from_hex_string(signal_bitval_str);

    if (bitval == 0)
        throw std::runtime_error("Error (line " + std::to_string(line_number) +
                                 "): Expected signal bit value to be > 0.");

    return bitval;
}

auto control_signals_parser::parse_signal_description(const std::vector<std::string> &line,
                                                      const unsigned line_number) const -> std::string
{
    auto signal_description = aeon::common::string::trimmed(line[2]);

    if (signal_description.empty())
        throw std::runtime_error("Error (line " + std::to_string(line_number) + "): Expected signal description.");

    return signal_description;
}

auto control_signals_parser::from_hex_string(const std::string &str) const -> std::uint64_t
{
    std::uint64_t value;
    std::istringstream iss(str);
    iss >> std::hex >> value;
    return value;
}

} // namespace rua
