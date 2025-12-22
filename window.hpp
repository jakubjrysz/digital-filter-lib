#pragma once
#include <vector>


enum class WindowType {
    Rectangular,
    Hann,
    Hamming,
    Blackman
};

std::vector<float> createWindow(WindowType type, size_t N);
