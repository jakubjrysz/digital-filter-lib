#include "window.hpp"
#include <cmath>

namespace jr {
    
    std::vector<float> createWindow(WindowType type, size_t N) {
    std::vector<float> w(N, 1.0f);


    switch (type) {
    case WindowType::Rectangular:
        break;

    case WindowType::Hann:
        for (size_t n = 0; n < N; ++n) {
            w[n] = 0.5f * (1.0f - std::cos(2.0f * PI * n / (N - 1)));
        }
        break;

    case WindowType::Hamming:
        for (size_t n = 0; n < N; ++n) {
            w[n] = 0.54f - 0.46f * std::cos(2.0f * PI * n / (N - 1));
        }
        break;

    case WindowType::Blackman:
        for (size_t n = 0; n < N; ++n) {
            w[n] = 0.42f - 0.5f * std::cos(2.0f * PI * n / (N - 1)) + 0.08f * std::cos(4.0f * PI * n / (N - 1));
        }
        break;
    }

    return w;
    }
}