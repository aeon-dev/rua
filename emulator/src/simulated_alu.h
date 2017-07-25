#pragma once

#include "ibus_transceiver.h"

class simulated_alu : public ibus_transceiver<8>
{
public:
    explicit simulated_alu(ibus_transceiver<8> &register_a, ibus_transceiver<8> &register_b);

    virtual ~simulated_alu();

    auto get_name() const -> std::string override;

    auto get_read_enabled() const -> bool override;

    auto get_output_enabled() const -> bool override;

    auto get_output() const -> typename ibus_transceiver<8>::type override;

    void set_read_enabled(const bool enable) override;

    void set_output_enabled(const bool enable) override;

    void set_output_value(const typename ibus_transceiver<8>::type value) override;

private:
    ibus_transceiver<8> &register_a_;
    ibus_transceiver<8> &register_b_;
    bool output_enabled_;
};
