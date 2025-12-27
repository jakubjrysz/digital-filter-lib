#include "iir_filter.hpp"

#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>

IIRFilter::IIRFilter(
    const std::vector<float>& bCoeffs,
    const std::vector<float>& aCoeffs
)
    : b(bCoeffs),
      a(aCoeffs),
      x(bCoeffs.size(), 0.0f),
      y(aCoeffs.size(), 0.0f)
{
    // zakładamy: a[0] == 1
}

float IIRFilter::processSample(float input)
{
    // przesuwamy historię wejścia
    for (size_t i = x.size() - 1; i > 0; --i)
        x[i] = x[i - 1];
    x[0] = input;

    float output = 0.0f;

    // część FIR (licznik)
    for (size_t i = 0; i < b.size(); ++i)
        output += b[i] * x[i];

    // część IIR (mianownik, bez a[0])
    for (size_t i = 1; i < a.size(); ++i)
        output -= a[i] * y[i];

    // przesuwamy historię wyjścia
    for (size_t i = y.size() - 1; i > 0; --i)
        y[i] = y[i - 1];
    y[0] = output;

    return output;
}

void IIRFilter::process(
    const float* input,
    float* output,
    size_t length
) {
    for (size_t i = 0; i < length; ++i)
        output[i] = processSample(input[i]);
}

void IIRFilter::reset()
{
    std::fill(x.begin(), x.end(), 0.0f);
    std::fill(y.begin(), y.end(), 0.0f);
}


size_t IIRFilter::order() const
{
    return std::max(b.size(), a.size()) - 1;
}
