#pragma once

#include "ibus_transceiver.h"

class simulated_alu : public ibus_transceiver8
{
public:
    explicit simulated_alu(ibus_transceiver8 &register_a, ibus_transceiver8 &register_b);

    virtual ~simulated_alu();

    auto get_name() const -> std::string override;

    auto get_read_enabled() const -> bool override;

    auto get_output_enabled() const -> bool override;

    auto get_output() const -> std::uint8_t override;

    void set_output_value(const std::uint8_t value) override;

    void update_control_flags(const std::uint64_t value) override;

private:
    ibus_transceiver8 &register_a_;
    ibus_transceiver8 &register_b_;
    bool output_enabled_;
};
