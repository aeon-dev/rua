#pragma once

#include "control_signals.h"
#include "header.h"
#include <memory>
#include <cstdint>
#include <vector>
#include <string>
#include <map>

namespace rua
{

class assembler
{
public:
    assembler();
    ~assembler() = default;

    bool parse_arguments(int argc, char *argv[]);
    void assemble();

private:
    void parse();

    void parse_file(const std::string &file);
    void parse_include(const std::string &line, int line_number);
    void parse_macro_call(const std::string &line, int line_number);
    void parse_instructions(const std::string &line, int line_number);

    void check_opcode_length(const int line_number) const;

    void write_output_roms();

    std::string input_file_;
    std::unique_ptr<control_signals_parser> signals_parser_;
    std::map<std::uint8_t, std::vector<std::uint64_t>> opcode_;
    std::map<std::string, std::vector<std::uint64_t>> macros_;

    header last_header_;
};

} // namespace rua
