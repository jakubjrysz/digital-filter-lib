#pragma once

#include <vector>
#include "filter.hpp"

namespace jr {

    /**
     * @brief Infinite Impulse Response (IIR) digital filter.
     *
     * Implements an IIR filter with given numerator (b) and denominator (a) coefficients.
     */
    class IIRFilter : public Filter {
    public:
        /**
         * @brief Default IIR constructor, b = 1; a = 1.
         */
        IIRFilter();

        /**
         * @brief Constructor with given filter coefficients.
         *
         * @param bCoeffs Numerator coefficients.
         * @param aCoeffs Denominator coefficients.
         *
         * @note The first element of aCoeffs is typically 1.0.
         */
        IIRFilter(const std::vector<float>& bCoeffs, const std::vector<float>& aCoeffs);

        /**
         * @brief Process a single input sample and return the filtered output.
         * @param x Input sample.
         * @return Filtered output sample.
         */
        float processSample(float x) override;

        /**
         * @brief Process a block of input samples.
         * @param input Pointer to input buffer.
         * @param output Pointer to output buffer.
         * @param length Number of samples to process.
         */
        void process(const float* input, float* output, size_t length) override;

        /**
         * @brief Update filter coefficients.
         *
         * @param bCoeffs New numerator coefficients.
         * @param aCoeffs New denominator coefficients.
         */
        void setCoefficients(const std::vector<float>& bCoeffs, const std::vector<float>& aCoeffs);

        /**
         * @brief Reset the filter state (internal buffers).
         */
        void reset() override;

        /**
         * @brief Get filter coefficients.
         * @return 2D vector containing {b, a} coefficient vectors.
         */
        std::vector<std::vector<float>> getCoeffs() override;

        /**
         * @brief Get the filter order (maximum of numerator and denominator order).
         * @return Filter order.
         */
        size_t getOrder() const override;

        bool operator==(const IIRFilter& other) const;
        bool operator!=(const IIRFilter& other) const;

    private:
        std::vector<float> b;  ///< Numerator (feedforward) coefficients
        std::vector<float> a;  ///< Denominator (feedback) coefficients
        std::vector<float> x;  ///< Input delay line
        std::vector<float> y;  ///< Output delay line
    };

}
