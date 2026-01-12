#include <iostream>
#include <vector>
#include <cmath>

#include "fir_filter.hpp"
#include "iir_filter.hpp"

int main() {
    using namespace jr;

    const float fs = 48000.0f;
    const float duration = 0.01f;
    const size_t N = fs * duration;

    FIRFilter firBandpass(
        FIRType::Bandpass,
        fs,
        5000,
        8000,
        40,
        WindowType::Blackman
    );

    std::vector<float> input(N);
    std::vector<float> output(N);

    const float f1 = 1000.0f;
    const float f2 = 6500;
    const float f3 = 12000.0f;

    for (size_t n = 0; n < N; ++n) {
        float t = n / fs;
        input[n] =
            std::sin(2.0f * PI * f1 * t) +
            std::sin(2.0f * PI * f2 * t) +
            std::sin(2.0f * PI * f3 * t);
    }

    firBandpass.reset();
    firBandpass.process(input.data(), output.data(), N);

    std::cout << "n\tinput\toutput\n";
    for (size_t i = 0; i < 150; ++i) {
        std::cout << i << "\t"
                  << input[i] << "\t"
                  << output[i] << "\n";
    }

    FIRFilter firLowpass(
            FIRType::Lowpass,
            48000.0f,
            1000.0f,
            10,
            WindowType::Hann
        );

        FIRFilter firLowpass2(FIRType::Bandpass, 48000, 12000, 15000, 10, WindowType::Blackman);

        std::cout << "FIR Lowpass filter created.\n";
        std::cout << "FIR order: " << firLowpass.getOrder() << "\n";

        auto firCoeffs = firLowpass.getCoeffs();
        std::cout << "FIR coefficients size: " << firCoeffs[0].size() << "\n";

        firLowpass.reset();
        std::cout << "FIR filter reset done.\n";

        std::vector<float> b = {0.2f, 0.2f, 0.2f};
        std::vector<float> a = {1.0f, -0.5f, 0.25f};

        IIRFilter iir(b, a);

        std::cout << "IIR filter created.\n";
        std::cout << "IIR order: " << iir.getOrder() << "\n";

        auto iirCoeffs = iir.getCoeffs();
        std::cout << "IIR b coefficients size: " << iirCoeffs[0].size() << "\n";
        std::cout << "IIR a coefficients size: " << iirCoeffs[1].size() << "\n";

        iir.reset();
        std::cout << "IIR filter reset done.\n";

        FIRFilter bam;
    return 0;
}
