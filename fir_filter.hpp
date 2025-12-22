#include <iostream>
#include <cmath>
#include <vector>
#include "filter.hpp"
#include "window.hpp"

class FIRFilter : public Filter {
public:
    explicit FIRFilter(const std::vector<float>& coeffs);

    FIRFilter(
        FIRType type,
        float fs,
        float f1,
        float f2,
        size_t order,
        WindowType windowType
    );

    float processSample(float x) override;

    void process(
        const float* input,
        float* output,
        size_t length
    ) override;

    void reset() override;
    size_t order() const override;

private:
    std::vector<float> b;
    std::vector<float> x;
};

enum class FIRType {
    Lowpass,
    Highpass,
    Bandpass,
    Bandstop
};