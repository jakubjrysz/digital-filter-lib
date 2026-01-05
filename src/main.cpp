#include <iostream>
#include "fir_filter.hpp"
#include "iir_filter.hpp"
#include "window.hpp"

int main() {
    using namespace jr;

    try {
        FIRFilter firLowpass(
            FIRType::Lowpass,
            48000.0f,
            1000.0f,
            10,
            WindowType::Hann
        );

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

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
