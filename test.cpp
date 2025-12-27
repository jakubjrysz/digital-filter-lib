#include <iostream>
#include <vector>
#include <cmath>

#include "fir_filter.hpp"

int main()
{
    const float fs = 48000.0f;
    const float fLow = 500.0f;
    const float fHigh = 8000.0f;
    const float cutoff = 2000.0f;

    const size_t order = 64;
    const size_t N = 256;

    // FIR Low-pass
    FIRFilter fir(
        FIRType::Lowpass,
        fs,
        cutoff,
        order,
        WindowType::Hann
    );

    std::vector<float> input(N);
    std::vector<float> output(N);

    // generowanie sygnału testowego
    for (size_t n = 0; n < N; ++n) {
        float t = static_cast<float>(n) / fs;
        input[n] =
            std::sin(2.0f * 3.14159265f * fLow * t) +
            0.5f * std::sin(2.0f * 3.14159265f * fHigh * t);
    }

    // filtracja
    fir.process(input.data(), output.data(), N);

    // wypisujemy kilka próbek
    std::cout << "n\tinput\t\toutput\n";
    for (size_t i = 0; i < 256; ++i) {
        std::cout << i << "\t"
                  << input[i] << "\t"
                  << output[i] << "\n";
    }
    std::cout << "\n fs: " << fir.getFs() << std::endl;
    return 0;
}
