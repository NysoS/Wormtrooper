#pragma once

#include <cstdint> // For using uint16_t

namespace JavaEngine
{
    using MButton = uint16_t;

    enum MouseButton : MButton
    {
        MouseLeft,
        MouseRight,
        MouseMiddle,
        MouseExtra1,
        MouseExtra2
    };
}