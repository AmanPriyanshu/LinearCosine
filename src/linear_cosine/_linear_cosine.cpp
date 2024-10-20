#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <cmath>

namespace py = pybind11;

union FloatBits {
    float value;
    unsigned int bits;
};

unsigned int extractMantissa(float value, int mantissaBits) {
    FloatBits fb;
    fb.value = value;
    return (fb.bits & 0x007FFFFF) >> (23 - mantissaBits);
}

int extractExponent(float value) {
    FloatBits fb;
    fb.value = value;
    return ((fb.bits & 0x7F800000) >> 23) - 127;
}

float lMul_l3(float x, float y, int mantissaBits) {
    unsigned int xMantissa = extractMantissa(x, mantissaBits);
    unsigned int yMantissa = extractMantissa(y, mantissaBits);
    int xExponent = extractExponent(x);
    int yExponent = extractExponent(y);

    float result = (1 + xMantissa / static_cast<float>(1 << mantissaBits) +
                       yMantissa / static_cast<float>(1 << mantissaBits) +
                       1.0 / (1 << mantissaBits)) *
                   std::pow(2, xExponent + yExponent);
    return result;
}

float lMul_4(float x, float y, int mantissaBits) {
    unsigned int xMantissa = extractMantissa(x, mantissaBits);
    unsigned int yMantissa = extractMantissa(y, mantissaBits);
    int xExponent = extractExponent(x);
    int yExponent = extractExponent(y);

    float result = (1 + xMantissa / static_cast<float>(1 << mantissaBits) +
                       yMantissa / static_cast<float>(1 << mantissaBits) +
                       0.125) *
                   std::pow(2, xExponent + yExponent);
    return result;
}

float lMul_g4(float x, float y, int mantissaBits) {
    unsigned int xMantissa = extractMantissa(x, mantissaBits);
    unsigned int yMantissa = extractMantissa(y, mantissaBits);
    int xExponent = extractExponent(x);
    int yExponent = extractExponent(y);

    float result = (1 + xMantissa / static_cast<float>(1 << mantissaBits) +
                       yMantissa / static_cast<float>(1 << mantissaBits) +
                       0.0625) *
                   std::pow(2, xExponent + yExponent);
    return result;
}

float lMul(float x, float y, int mantissaBits) {
    if (mantissaBits <= 3) {
        return lMul_l3(x, y, mantissaBits);
    } else if (mantissaBits == 4) {
        return lMul_4(x, y, mantissaBits);
    } else {
        return lMul_g4(x, y, mantissaBits);
    }
}

float mul(float x, float y, int mantissaBits) {
    unsigned int xMantissa = extractMantissa(x, mantissaBits);
    unsigned int yMantissa = extractMantissa(y, mantissaBits);
    int xExponent = extractExponent(x);
    int yExponent = extractExponent(y);

    float result = (1 + xMantissa / static_cast<float>(1 << mantissaBits)) *
                   std::pow(2, xExponent) *
                   (1 + yMantissa / static_cast<float>(1 << mantissaBits)) *
                   std::pow(2, yExponent);
    return result;
}

float cosine_similarity(const std::vector<float>& v1, const std::vector<float>& v2, int mantissaBits, bool use_lmul) {
    if (v1.size() != v2.size()) {
        throw std::invalid_argument("Vectors must have the same length");
    }

    float dotProduct = 0;
    float norm1 = 0;
    float norm2 = 0;

    auto mulFunc = use_lmul ? lMul : mul;

    for (size_t i = 0; i < v1.size(); i++) {
        dotProduct += mulFunc(v1[i], v2[i], mantissaBits);
        norm1 += mulFunc(v1[i], v1[i], mantissaBits);
        norm2 += mulFunc(v2[i], v2[i], mantissaBits);
    }

    return dotProduct / std::sqrt(norm1 * norm2);
}

PYBIND11_MODULE(_linear_cosine, m) {
    m.doc() = "Linear and Standard Cosine Similarity implementation in C++";
    m.def("cosine_similarity", &cosine_similarity, 
          "Compute cosine similarity using either linear or standard multiplication",
          py::arg("v1"), py::arg("v2"), py::arg("mantissa_bits") = 8, py::arg("use_lmul") = true);
}