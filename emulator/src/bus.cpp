#include "bus.h"

template class bus<8>;
template class bus<16>;

template <int bits_t>
auto bus<bits_t>::get_value() const
{
    for (const auto transceiver : transceivers_)
    {
        if (transceiver->get_output_enabled())
            return transceiver->get_output();
    }

    return typename bits_to_type_trait<bits_t>::type(0);
}

template <int bits_t>
void bus<bits_t>::tick()
{
    check_bus_collisions();
    transfer_data();
}

template <int bits_t>
void bus<bits_t>::connect_transceiver(ibus_transceiver<bits_t> &transceiver)
{
    transceivers_.push_back(&transceiver);
}

template <int bits_t>
void bus<bits_t>::check_bus_collisions()
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

template <int bits_t>
void bus<bits_t>::transfer_data()
{
    auto value = get_value();

    for (const auto transceiver : transceivers_)
    {
        if (transceiver->get_read_enabled())
            transceiver->set_output_value(value);
    }
}
