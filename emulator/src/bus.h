#pragma once

#include "ibus_transceiver.h"
#include "module.h"
#include <vector>

template <int bits_t>
class bus
{
public:
    bus() = default;
    virtual ~bus() = default;

    auto get_value() const;

    void tick();

    void connect_transceiver(ibus_transceiver<bits_t> &transceiver);

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

    std::vector<ibus_transceiver<bits_t> *> transceivers_;
};
