#pragma once

#include <control_signals.h>

class module
{
public:
    module() = default;
    virtual ~module() = default;

    virtual void on_control_signal_changed(const cs line, const bool value) = 0;
};
