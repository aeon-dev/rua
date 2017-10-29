#pragma once

#include <string>
#include <cstdint>

class ibus_transceiver8
{
public:
    ibus_transceiver8() = default;
    virtual ~ibus_transceiver8() = default;

    virtual auto get_name() const -> std::string = 0;
    virtual auto get_read_enabled() const -> bool = 0;
    virtual auto get_output_enabled() const -> bool = 0;

    virtual auto get_output() const -> std::uint8_t = 0;

    virtual void set_output_value(const std::uint8_t value) = 0;

    virtual void update_control_flags(const std::uint64_t value) = 0;
};
