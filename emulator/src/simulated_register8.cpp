#include "simulated_register8.h"

simulated_register8::simulated_register8(const std::string &name)
    : name_(name)
    , read_enabled_(false)
    , output_enabled_(false)
    , value_()
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

auto simulated_register8::get_output() const -> ibus_transceiver<8>::type
{
    return value_;
}

void simulated_register8::set_read_enabled(const bool enable)
{
    read_enabled_ = enable;
}

void simulated_register8::set_output_enabled(const bool enable)
{
    output_enabled_ = enable;
}

void simulated_register8::set_output_value(const ibus_transceiver<8>::type value)
{
    value_ = value;
}
