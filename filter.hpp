#pragma once

#include <cstddef>
#include <vector>

namespace jr{

    class Filter {
        public:
            virtual ~Filter() = default;

            virtual float processSample(float x) = 0;

            virtual void process(
                const float* input,
                float* output,
                size_t length
            ) = 0;

            virtual std::vector <std::vector<float>> getCoeffs();
            virtual void reset() = 0;
            virtual size_t getOrder() const = 0;
    };
}
