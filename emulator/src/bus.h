#pragma once

#include "ibus_transceiver.h"
#include <vector>

class bus
{
public:
    bus() = default;
    virtual ~bus() = default;

    auto get_value() const -> std::uint8_t;

    void tick();

    void connect_transceiver(ibus_transceiver8 &transceiver);

private:
    /*!
     * Check mainly for debugging purposes if any devices is writing on the bus
     * at the same time as another device.
     */
    void check_bus_collisions();

    /*!
     * Transfer data from the outputting transceiver to any that have their
     * write enabled.
     */
    void transfer_data();

    std::vector<ibus_transceiver8 *> transceivers_;
};
