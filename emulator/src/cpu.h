#pragma once

#include "bus.h"
#include "ibus_transceiver.h"
#include <memory>

class cpu
{
public:
    cpu();

    virtual ~cpu();

    void tick();

private:
    void register_simulated_modules();

    bus databus_;

    std::unique_ptr<ibus_transceiver8> register_a_;
    std::unique_ptr<ibus_transceiver8> register_b_;
    std::unique_ptr<ibus_transceiver8> register_x_;
    std::unique_ptr<ibus_transceiver8> register_y_;
    std::unique_ptr<ibus_transceiver8> alu_;
};
