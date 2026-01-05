#pragma once

#include <cstddef>
#include <vector>

/// @brief Mathematical constant pi
constexpr float PI = 3.14159265f;

namespace jr {

    /**
     * @brief Types of window functions for FIR filter design.
     */
    enum class WindowType {
        Rectangular,  ///< Rectangular
        Hann,         ///< Hann window
        Hamming,      ///< Hamming window
        Blackman      ///< Blackman window
    };

    /**
     * @brief Generate a window of length N.
     *
     * This function returns a vector of N window coefficients
     * according to the specified WindowType.
     *
     * @param type The type of window to generate.
     * @param N Length of the window (number of samples).
     * @return std::vector<float> containing N window coefficients.
     */
    std::vector<float> createWindow(WindowType type, size_t N);

} // namespace jr
