#include "cpu.h"
#include "simulated_register8.h"
#include "simulated_alu.h"

cpu::cpu()
    : register_a_(std::make_unique<simulated_register8>("A", 0, 0))
    , register_b_(std::make_unique<simulated_register8>("B", 0, 0))
    , register_x_(std::make_unique<simulated_register8>("X", 0, 0))
    , register_y_(std::make_unique<simulated_register8>("Y", 0, 0))
    , alu_(std::make_unique<simulated_alu>(*register_a_, *register_b_))
{
    register_simulated_modules();
}

cpu::~cpu() = default;

void cpu::tick()
{
    databus_.tick();
}

void cpu::register_simulated_modules()
{
    databus_.connect_transceiver(*register_a_);
    databus_.connect_transceiver(*register_b_);
    databus_.connect_transceiver(*register_x_);
    databus_.connect_transceiver(*register_y_);
}
