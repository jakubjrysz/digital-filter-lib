#pragma once

#include <vector>
#include <stdexcept>
#include "filter.hpp"
#include "window.hpp"

constexpr float PI = 3.14159265f;

namespace jr {

    enum class FIRType {
        Lowpass,
        Highpass,
        Bandpass,
        Bandstop
    };

    class FIRFilter : public Filter {
        public:
            FIRFilter(
                FIRType type,
                float fs,
                float fc,
                size_t order,
                WindowType windowType
            );

            FIRFilter(
                FIRType type,
                float fs,
                float f1,
                float f2,
                size_t order,
                WindowType windowType
            );

            float processSample(float x) override;
            
            void process(const float* input, float* output, size_t length) override;
            
            void reset() override;
            
            std::vector <std::vector<float>> getCoeffs() override;
            
            size_t getOrder() const override;
            
            float getFs();

        private:
            std::vector<float> b;
            std::vector<float> x;
            float fs;
    };
}