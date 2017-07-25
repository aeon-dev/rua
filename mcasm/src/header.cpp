#include "header.h"
#include <aeon/common/string.h>
#include <iostream>

namespace rua
{

header::header()
    : type_(header_type::none)
    , name_()
    , opcode_(-1)
{
}

header::header(const std::string &line, int line_number)
    : type_(header_type::none)
    , name_()
    , opcode_(-1)
{
    parse_header_name(line, line_number);
    parse_by_type();
}

auto header::get_type() const -> header_type
{
    return type_;
}

auto header::get_opcode() const -> std::uint8_t
{
    return static_cast<std::uint8_t>(opcode_);
}

auto header::get_name() const -> std::string
{
    return name_;
}

void header::debug_print() const
{
    switch (type_)
    {
        case header_type::opcode:
            std::cout << "Opcode header: " << opcode_ << "\n";
            break;
        case header_type::macro:
            std::cout << "Macro header: '" << name_ << "'\n";
            break;
        case header_type::none:
        default:
            std::cout << "Empty or invalid header.\n";
    }
}

void header::parse_header_name(const std::string &line, int line_number)
{
    if (aeon::common::string::right(line, 1) != "]")
        throw std::runtime_error("Error (line " + std::to_string(line_number) + "): Expected ']'.");

    name_ = aeon::common::string::strip_both(line, 1);
}

void header::parse_by_type()
{
    if (is_opcode())
        to_opcode();
    else
        type_ = header_type::macro;
}

auto header::is_opcode() const -> bool
{
    if (name_.size() != 4)
        return false;

    if (name_[0] != '0' || name_[1] != 'x')
        return false;

    return true;
}

void header::to_opcode()
{
    type_ = header_type::opcode;
    opcode_ = aeon::common::string::hex_string_to_int<int>(name_);
}

} // namespace rua
