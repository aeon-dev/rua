#include "simulated_register8.h"
#include <aeon/common/bitflags.h>

simulated_register8::simulated_register8(const std::string &name, const std::uint64_t read_bit, const std::uint64_t write_bit)
    : name_(name)
    , read_enabled_(false)
    , output_enabled_(false)
    , value_()
    , read_bit_(read_bit)
    , write_bit_(write_bit)
{
}

simulated_register8::~simulated_register8() = default;

auto simulated_register8::get_name() const -> std::string
{
    return name_;
}

auto simulated_register8::get_read_enabled() const -> bool
{
    return read_enabled_;
}

auto simulated_register8::get_output_enabled() const -> bool
{
    return output_enabled_;
}

auto simulated_register8::get_output() const -> std::uint8_t
{
    return value_;
}

void simulated_register8::set_output_value(const std::uint8_t value)
{
    value_ = value;
}

void simulated_register8::update_control_flags(const std::uint64_t value)
{
    read_enabled_ = aeon::common::check_bit_flag(value, read_bit_);
    output_enabled_ = aeon::common::check_bit_flag(value, write_bit_);
}
