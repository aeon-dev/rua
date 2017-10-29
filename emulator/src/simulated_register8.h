#pragma once

#include "ibus_transceiver.h"

class simulated_register8 : public ibus_transceiver8
{
public:
    explicit simulated_register8(const std::string &name, const std::uint64_t read_bit, const std::uint64_t write_bit);

    virtual ~simulated_register8();

    auto get_name() const -> std::string override;

    auto get_read_enabled() const -> bool override;

    auto get_output_enabled() const -> bool override;

    auto get_output() const -> std::uint8_t override;

    void set_output_value(const std::uint8_t value) override;

    void update_control_flags(const std::uint64_t value) override;

protected:
    std::string name_;
    bool read_enabled_;
    bool output_enabled_;
    std::uint8_t value_;
    std::uint64_t read_bit_;
    std::uint64_t write_bit_;
};
