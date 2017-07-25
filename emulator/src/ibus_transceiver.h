#pragma once

#include <string>
#include <cstdint>

template <int bits_t>
struct bits_to_type_trait
{
};

template <>
struct bits_to_type_trait<8>
{
    using type = std::uint8_t;
};

template <>
struct bits_to_type_trait<16>
{
    using type = std::uint16_t;
};

template <int bits_t>
class ibus_transceiver
{
public:
    using type = typename bits_to_type_trait<bits_t>::type;

    ibus_transceiver() = default;
    virtual ~ibus_transceiver() = default;

    virtual auto get_name() const -> std::string = 0;
    virtual auto get_read_enabled() const -> bool = 0;
    virtual auto get_output_enabled() const -> bool = 0;

    virtual auto get_output() const -> type = 0;

    virtual void set_read_enabled(const bool enable) = 0;
    virtual void set_output_enabled(const bool enable) = 0;
    virtual void set_output_value(const type value) = 0;
};
