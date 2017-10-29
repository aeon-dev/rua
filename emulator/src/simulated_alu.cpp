#include "simulated_alu.h"

simulated_alu::simulated_alu(ibus_transceiver8 &register_a, ibus_transceiver8 &register_b)
    : register_a_(register_a)
    , register_b_(register_b)
    , output_enabled_(false)
{
}

simulated_alu::~simulated_alu() = default;

auto simulated_alu::get_name() const -> std::string
{
    return "Simulated ALU";
}

auto simulated_alu::get_read_enabled() const -> bool
{
    return false;
}

auto simulated_alu::get_output_enabled() const -> bool
{
    return output_enabled_;
}

auto simulated_alu::get_output() const -> std::uint8_t
{
    return register_a_.get_output() + register_b_.get_output();
}

void simulated_alu::set_output_value(const std::uint8_t)
{
    throw std::runtime_error("Unexpected read in simulated ALU");
}

void simulated_alu::update_control_flags(const std::uint64_t)
{
}
