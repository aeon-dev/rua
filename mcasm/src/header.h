#pragma once

#include <string>

namespace rua
{

enum class header_type
{
    none,
    opcode,
    macro
};

class header
{
public:
    header();
    header(const std::string &line, int line_number);

    auto get_type() const -> header_type;
    auto get_opcode() const -> std::uint8_t;
    auto get_name() const -> std::string;

    void debug_print() const;

private:
    void parse_header_name(const std::string &line, int line_number);
    void parse_by_type();
    auto is_opcode() const -> bool;
    void to_opcode();

    header_type type_;
    std::string name_;
    int opcode_;
};

} // namespace rua
