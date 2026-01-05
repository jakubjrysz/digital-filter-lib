#pragma once

#include <vector>
#include "filter.hpp"

namespace jr {

    class IIRFilter : public Filter {
        public:

            IIRFilter(const std::vector<float>& bCoeffs, const std::vector<float>& aCoeffs);

            float processSample(float x) override;

            void process(const float* input, float* output, size_t length) override;
            
            void setCoefficients(const std::vector<float>& bCoeffs, const std::vector<float>& aCoeffs);
            
            void reset() override;
            
            std::vector <std::vector<float>> getCoeffs() override;
            
            size_t getOrder() const override;

        private:
            std::vector<float> b;
            std::vector<float> a;
            
            std::vector<float> x;
            std::vector<float> y;
    };

}