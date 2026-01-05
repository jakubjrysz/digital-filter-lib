#pragma once

#include <cstddef>
#include <vector>

constexpr float PI = 3.14159265f;

namespace jr {

    enum class WindowType {
        Rectangular,
        Hann,
        Hamming,
        Blackman
    };

    std::vector<float> createWindow(WindowType type, size_t N);
}