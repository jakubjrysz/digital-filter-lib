#include "fir_filter.hpp"
#include "window.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

FIRFilter::FIRFilter(
    FIRType type,
    float fs,
    float f1,
    float f2,
    size_t order,
    WindowType windowType
) : b(order + 1, 0.0f), x(order + 1, 0.0f)
{
    const float pi = 3.14159265358979323846f;
    int mid = order / 2;

    // generujemy okno
    std::vector<float> w = createWindow(windowType, order + 1);

    // normalizacja częstotliwości
    float fc1 = f1 / (fs / 2.0f);
    float fc2 = f2 / (fs / 2.0f);

    for (size_t n = 0; n <= order; ++n) {
        int k = n - mid;
        float h = 0.0f;

        switch (type) {
        case FIRType::Lowpass:
            if (k == 0)
                h = 2.0f * fc1;
            else
                h = sin(2.0f * pi * fc1 * k) / (pi * k);
            break;

        case FIRType::Highpass:
            if (k == 0)
                h = 1.0f - 2.0f * fc1;
            else
                h = -sin(2.0f * pi * fc1 * k) / (pi * k);
            break;

        case FIRType::Bandpass:
            if (k == 0)
                h = 2.0f * (fc2 - fc1);
            else
                h = (sin(2.0f * pi * fc2 * k) - sin(2.0f * pi * fc1 * k)) / (pi * k);
            break;

        case FIRType::Bandstop:
            if (k == 0)
                h = 1.0f - 2.0f * (fc2 - fc1);
            else
                h = (sin(2.0f * pi * fc1 * k) - sin(2.0f * pi * fc2 * k)) / (pi * k);
            break;
        }

        b[n] = h * w[n]; // zastosowanie okna
    }
}


// przetwarzanie jednej próbki (sample-by-sample)
float FIRFilter::processSample(float input) {
    // przesuwamy bufor
    for (size_t i = x.size() - 1; i > 0; --i)
        x[i] = x[i - 1];

    x[0] = input;

    // splot
    float y = 0.0f;
    for (size_t i = 0; i < b.size(); ++i)
        y += b[i] * x[i];

    return y;
}

// przetwarzanie całego bloku / sygnału
void FIRFilter::process(const float* input, float* output, size_t length) {
    for (size_t i = 0; i < length; ++i)
        output[i] = processSample(input[i]);
}

// reset bufora (np. przy nowym sygnale)
void FIRFilter::reset() {
    std::fill(x.begin(), x.end(), 0.0f);
}

// zwraca rząd filtru = liczba współczynników - 1
size_t FIRFilter::order() const {
    return b.size() - 1;
}
