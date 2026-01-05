#include "fir_filter.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

namespace jr {

    FIRFilter::FIRFilter(
        FIRType type,
        float fs,
        float fc,
        size_t order,
        WindowType windowType
    ) : b(order + 1, 0.0f), x(order + 1, 0.0f), fs(fs)
    {
        if (type != FIRType::Lowpass && type != FIRType::Highpass)
            throw std::invalid_argument("FIRFilter: invalid type for LP/HP");

        if (fs <= 0.0f)
            throw std::invalid_argument("FIRFilter: fs must be > 0");

        if (order == 0 || order % 2 != 0)
            throw std::invalid_argument("FIRFilter: order must be even and > 0");

        if (fc <= 0.0f || fc >= fs / 2.0f)
            throw std::invalid_argument("FIRFilter: fc out of range");

        int mid = order / 2;

        std::vector<float> w = createWindow(windowType, order + 1);
        float fcNorm = fc / (fs / 2.0f);

        for (size_t n = 0; n <= order; ++n) {
            int k = n - mid;
            float h = 0.0f;

            if (type == FIRType::Lowpass) {
                if (k == 0)
                    h = 2.0f * fcNorm;
                else
                    h = sin(2.0f * PI * fcNorm * k) / (PI * k);
            } else {
                if (k == 0)
                    h = 1.0f - 2.0f * fcNorm;
                else
                    h = -sin(2.0f * PI * fcNorm * k) / (PI * k);
            }

            b[n] = h * w[n];
        }
    }

    FIRFilter::FIRFilter(
        FIRType type,
        float fs,
        float f1,
        float f2,
        size_t order,
        WindowType windowType
    ) : b(order + 1, 0.0f), x(order + 1, 0.0f), fs(fs)
    {
        if (type != FIRType::Bandpass && type != FIRType::Bandstop)
            throw std::invalid_argument("FIRFilter: invalid type for BP/BS");

        if (fs <= 0.0f)
            throw std::invalid_argument("FIRFilter: fs must be > 0");

        if (order == 0 || order % 2 != 0)
            throw std::invalid_argument("FIRFilter: order must be even and > 0");

        if (f1 <= 0.0f || f2 <= 0.0f || f1 >= f2)
            throw std::invalid_argument("FIRFilter: invalid band");

        if (f2 >= fs / 2.0f)
            throw std::invalid_argument("FIRFilter: f2 out of range");

        int mid = order / 2;

        std::vector<float> w = createWindow(windowType, order + 1);
        float fc1 = f1 / (fs / 2.0f);
        float fc2 = f2 / (fs / 2.0f);

        for (size_t n = 0; n <= order; ++n) {
            int k = n - mid;
            float h = 0.0f;

            if (k == 0) {
                h = (type == FIRType::Bandpass)
                    ? 2.0f * (fc2 - fc1)
                    : 1.0f - 2.0f * (fc2 - fc1);
            } else {
                float s1 = sin(2.0f * PI * fc1 * k);
                float s2 = sin(2.0f * PI * fc2 * k);

                h = (type == FIRType::Bandpass)
                    ? (s2 - s1) / (PI * k)
                    : (s1 - s2) / (PI * k);
            }

            b[n] = h * w[n];
        }
    }


    float FIRFilter::processSample(float input) {

        for (size_t i = x.size() - 1; i > 0; --i)
            x[i] = x[i - 1];

        x[0] = input;

        float y = 0.0f;
        for (size_t i = 0; i < b.size(); ++i)
            y += b[i] * x[i];

        return y;
    }

    void FIRFilter::process(const float* input, float* output, size_t length) {
        for (size_t i = 0; i < length; ++i)
            output[i] = processSample(input[i]);
    }

    void FIRFilter::reset() {
        std::fill(x.begin(), x.end(), 0.0f);
    }

    std::vector <std::vector<float>> FIRFilter::getCoeffs(){
        return { b };
    }

    size_t FIRFilter::getOrder() const {
        return b.size() - 1;
    }

    float FIRFilter::getFs(){
        return fs;
    }
}