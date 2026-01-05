#pragma once

#include <cstddef>
#include <vector>

namespace jr {

    /**
     * @brief Abstract base class for digital filters.
     */
    class Filter {
    public:
        /**
         * @brief Virtual destructor.
         */
        virtual ~Filter() = default;

        /**
         * @brief Process a single input sample and return the output sample.
         * 
         * @param x Input sample.
         * @return Filtered output sample.
         */
        virtual float processSample(float x) = 0;

        /**
         * @brief Process a block of input samples.
         * 
         * @param input Pointer to the input buffer.
         * @param output Pointer to the output buffer.
         * @param length Number of samples to process.
         */
        virtual void process(
            const float* input,
            float* output,
            size_t length
        ) = 0;

        /**
         * @brief Get filter coefficients.
         * 
         * @return 2D vector of filter coefficients.
         */
        virtual std::vector<std::vector<float>> getCoeffs() = 0;

        /**
         * @brief Reset the filter state (internal buffers).
         */
        virtual void reset() = 0;

        /**
         * @brief Get the filter order.
         * 
         * @return Order of the filter.
         */
        virtual size_t getOrder() const = 0;
    };

} // namespace jr
