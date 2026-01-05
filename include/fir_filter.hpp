#pragma once

#include <vector>
#include <stdexcept>
#include "filter.hpp"
#include "window.hpp"


namespace jr {

    /**
     * @brief Types of FIR filters.
     *
     * Defines the basic filter types supported by FIRFilter.
     */
    enum class FIRType {
        Lowpass,   ///< Low-pass filter
        Highpass,  ///< High-pass filter
        Bandpass,  ///< Band-pass filter
        Bandstop   ///< Band-stop filter
    };

    /**
     * @brief Finite Impulse Response (FIR) digital filter.
     *
     * Implements an FIR filter with configurable type, order,
     * cutoff frequencies, and windowing.
     */
    class FIRFilter : public Filter {
    public:
        /**
         * @brief Constructor for low-pass or high-pass FIR filter.
         *
         * @param type FIRType::Lowpass or FIRType::Highpass.
         * @param fs Sampling frequency (Hz), must be > 0.
         * @param fc Cutoff frequency (Hz), must be in (0, fs/2).
         * @param order Filter order, must be even and > 0.
         * @param windowType Window function to apply to the filter coefficients.
         *
         * @throw std::invalid_argument if parameters are out of range or type is invalid.
         */
        FIRFilter(
            FIRType type,
            float fs,
            float fc,
            size_t order,
            WindowType windowType
        );

        /**
         * @brief Constructor for band-pass or band-stop FIR filter.
         *
         * @param type FIRType::Bandpass or FIRType::Bandstop.
         * @param fs Sampling frequency (Hz), must be > 0.
         * @param f1 Lower cutoff frequency (Hz), must satisfy 0 < f1 < f2 < fs/2.
         * @param f2 Upper cutoff frequency (Hz), must satisfy f1 < f2 < fs/2.
         * @param order Filter order, must be even and > 0.
         * @param windowType Window function to apply to the filter coefficients.
         *
         * @throw std::invalid_argument if parameters are out of range or type is invalid.
         */
        FIRFilter(
            FIRType type,
            float fs,
            float f1,
            float f2,
            size_t order,
            WindowType windowType
        );

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
         * @brief Reset the filter state (internal delay buffer).
         */
        void reset() override;

        /**
         * @brief Get filter coefficients.
         * @return 2D vector containing filter coefficients.
         */
        std::vector<std::vector<float>> getCoeffs() override;

        /**
         * @brief Get filter order.
         * @return Filter order.
         */
        size_t getOrder() const override;

        /**
         * @brief Get the sampling frequency.
         * @return Sampling frequency in Hz.
         */
        float getFs();

    private:
        std::vector<float> b;  ///< Filter coefficients
        std::vector<float> x;  ///< Delay line (internal buffer)
        float fs;              ///< Sampling frequency
    };

} // namespace jr
