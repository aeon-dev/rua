#include "bus.h"

auto bus::get_value() const -> std::uint8_t
{
    for (const auto transceiver : transceivers_)
    {
        if (transceiver->get_output_enabled())
            return transceiver->get_output();
    }

    return 0;
}

void bus::tick()
{
    check_bus_collisions();
    transfer_data();
}

void bus::connect_transceiver(ibus_transceiver8 &transceiver)
{
    transceivers_.push_back(&transceiver);
}

void bus::check_bus_collisions()
{
    bool device_active = false;
    for (const auto transceiver : transceivers_)
    {
        // If more than one device is outputting to the bus,
        // there is a collision.
        if (transceiver->get_output_enabled())
        {
            if (device_active)
            {
                throw std::runtime_error("Bus collision!");
            }

            device_active = true;
        }
    }
}

void bus::transfer_data()
{
    const auto value = get_value();

    for (const auto transceiver : transceivers_)
    {
        if (transceiver->get_read_enabled())
            transceiver->set_output_value(value);
    }
}
