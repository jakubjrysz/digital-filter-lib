# digital filter lib

A small C++ library implementing basic **digital signal processing filters**:
- FIR filters (Lowpass, Highpass, Bandpass, Bandstop)
- IIR filters with arbitrary coefficients
- Window functions (Rectangular, Hann, Hamming, Blackman)

The project is designed with **real-time audio processing** in mind:
- no dynamic allocation during processing
- pointer-based buffer API
- simple and extensible class hierarchy

---

## Features

- FIR filter design using the window method
- IIR filter processing using difference equations
- Unified abstract `Filter` interface
- Sample-by-sample and block-based processing
- Clean separation into `include/` and `src/`
- CMake-based build system
- Simple test application

---

## Project Structure
```bash
├── CMakeLists.txt
├── README.md
├── main_example.ods
├── digital_filter_JR.pdf
├── include/
│ ├── filter.hpp
│ ├── fir_filter.hpp
│ ├── iir_filter.hpp
│ └── window.hpp
├── src/
│ ├── fir_filter.cpp
│ ├── iir_filter.cpp
│ ├── window.cpp
│ └── main.cpp
```
## Requirements

- Linux (tested on GCC)
- C++17 compatible compiler (GCC ≥ 9, Clang ≥ 10)
- CMake ≥ 3.10

## Build Instructions
```bash
git clone <repository_url>
cd <repository_name>
mkdir build
cd build
make
./test_filters
```