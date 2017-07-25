#pragma once

#include "ibus_transceiver.h"

class simulated_register8 : public ibus_transceiver<8>
{
public:
    explicit simulated_register8(const std::string &name);

    virtual ~simulated_register8();

    auto get_name() const -> std::string override;

    auto get_read_enabled() const -> bool override;

    auto get_output_enabled() const -> bool override;

    auto get_output() const -> typename ibus_transceiver<8>::type override;

    void set_read_enabled(const bool enable) override;

    void set_output_enabled(const bool enable) override;

    void set_output_value(const typename ibus_transceiver<8>::type value) override;

protected:
    std::string name_;
    bool read_enabled_;
    bool output_enabled_;
    typename ibus_transceiver<8>::type value_;
};
