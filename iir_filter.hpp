#pragma once

#include <vector>
#include "filter.hpp"

class IIRFilter : public Filter {
public:
    // b – współczynniki licznika
    // a – współczynniki mianownika (a[0] MUSI być = 1)
    IIRFilter(
        const std::vector<float>& bCoeffs,
        const std::vector<float>& aCoeffs
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
    std::vector<float> b;   // licznik
    std::vector<float> a;   // mianownik

    std::vector<float> x;   // historia wejścia
    std::vector<float> y;   // historia wyjścia
};
