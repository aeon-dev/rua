#include "simulated_alu.h"

simulated_alu::simulated_alu(ibus_transceiver<8> &register_a, ibus_transceiver<8> &register_b)
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

auto simulated_alu::get_output() const -> ibus_transceiver<8>::type
{
    return register_a_.get_output() + register_b_.get_output();
}

void simulated_alu::set_read_enabled(const bool)
{
    throw std::runtime_error("Unexpected read enable in simulated ALU");
}

void simulated_alu::set_output_enabled(const bool enable)
{
    output_enabled_ = false;
}

void simulated_alu::set_output_value(const ibus_transceiver<8>::type)
{
    throw std::runtime_error("Unexpected read in simulated ALU");
}
