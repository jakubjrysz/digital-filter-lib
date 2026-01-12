#include "iir_filter.hpp"

#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace jr {
    IIRFilter::IIRFilter() : b{1.0f}, a{1.0f}, x(1, 0.0f), y(1, 0.0f){}

    IIRFilter::IIRFilter(const std::vector<float>& bCoeffs, const std::vector<float>& aCoeffs)
        : b(bCoeffs),
        a(aCoeffs),
        x(bCoeffs.size(), 0.0f),
        y(aCoeffs.size(), 0.0f)
    {
        if (b.empty())
            throw std::invalid_argument("IIRFilter: b coefficients empty");

        if (a.empty())
            throw std::invalid_argument("IIRFilter: a coefficients empty");

        if (a[0] != 1)
            throw std::invalid_argument("IIRFilter: a[0] must be 1");

    }

    float IIRFilter::processSample(float input)
    {
        for (size_t i = x.size() - 1; i > 0; --i)
            x[i] = x[i - 1];
        x[0] = input;

        float output = 0.0f;

        for (size_t i = 0; i < b.size(); ++i)
            output += b[i] * x[i];

        for (size_t i = 1; i < a.size(); ++i)
            output -= a[i] * y[i];

        for (size_t i = y.size() - 1; i > 0; --i)
            y[i] = y[i - 1];
        y[0] = output;

        return output;
    }

    void IIRFilter::process(const float* input, float* output, size_t length) {
        for (size_t i = 0; i < length; ++i)
            output[i] = processSample(input[i]);
    }

    std::vector <std::vector<float>> IIRFilter::getCoeffs(){
        return { b, a };
    }

    void IIRFilter::reset()
    {
        std::fill(x.begin(), x.end(), 0.0f);
        std::fill(y.begin(), y.end(), 0.0f);
    }

    size_t IIRFilter::getOrder() const
    {
        return std::max(b.size(), a.size()) - 1;
    }

    void IIRFilter::setCoefficients(const std::vector<float>& bCoeffs, const std::vector<float>& aCoeffs)
    {
        if(bCoeffs.empty()){
            throw std::invalid_argument("IIRFilter: bCoeffs empty");
        }

        if (aCoeffs.empty()){
            throw std::invalid_argument("IIRFilter: aCoeffs empty");
        }

        if (aCoeffs[0] != 1){
            throw std::invalid_argument("IIRFilter: aCoeffs[0] must be 1");
        }

        b = bCoeffs;
        a = aCoeffs;

        x.assign(b.size(), 0.0f);
        y.assign(a.size(), 0.0f);
    }

}