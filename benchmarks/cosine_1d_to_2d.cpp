#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

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
                   pow(2, xExponent + yExponent);
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
                   pow(2, xExponent + yExponent);
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
                   pow(2, xExponent + yExponent);
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
                   pow(2, xExponent) *
                   (1 + yMantissa / static_cast<float>(1 << mantissaBits)) *
                   pow(2, yExponent);
    return result;
}

template <typename MulFunc>
vector<float> cosineSimilarity1D2D(const vector<float>& v1, const vector<vector<float>>& v2, int mantissaBits, MulFunc mulFunc) {
    vector<float> similarities;
    for (const auto& v2i : v2) {
        float dotProduct = 0;
        float norm1 = 0;
        float norm2 = 0;

        for (int i = 0; i < v1.size(); i++) {
            dotProduct += mulFunc(v1[i], v2i[i], mantissaBits);
            norm1 += mulFunc(v1[i], v1[i], mantissaBits);
            norm2 += mulFunc(v2i[i], v2i[i], mantissaBits);
        }

        similarities.push_back(dotProduct / sqrt(norm1 * norm2));
    }
    return similarities;
}

vector<float> standardCosineSimilarity1D2D(const vector<float>& v1, const vector<vector<float>>& v2) {
    vector<float> similarities;
    for (const auto& v2i : v2) {
        float dotProduct = 0;
        float norm1 = 0;
        float norm2 = 0;

        for (int i = 0; i < v1.size(); i++) {
            dotProduct += v1[i] * v2i[i];
            norm1 += v1[i] * v1[i];
            norm2 += v2i[i] * v2i[i];
        }

        similarities.push_back(dotProduct / sqrt(norm1 * norm2));
    }
    return similarities;
}

int main() {
    vector<float> v1 = {1.04384, 2.03884, 3.03184849};
    vector<vector<float>> v2 = {
        {4.085858, 5.0, 6.0},
        {1.5, 2.5, 3.5},
        {0.5, 1.5, 2.5}
    };
    int N = 100000;

    long long standardTotalTime = 0;
    vector<float> standardSimilarities;

    for (int i = 0; i < N; i++) {
        auto start = high_resolution_clock::now();
        standardSimilarities = standardCosineSimilarity1D2D(v1, v2);
        auto stop = high_resolution_clock::now();
        auto durationStandard = duration_cast<nanoseconds>(stop - start);
        standardTotalTime += durationStandard.count();
    }

    long long standardAvgTime = standardTotalTime / N;

    cout << "Standard Cosine Similarities: ";
    for (float sim : standardSimilarities) {
        cout << sim << " ";
    }
    cout << endl;
    cout << "Standard Cosine Similarity Average Time (ns): " << standardAvgTime << endl;
    cout << endl;

    cout << "Mantissa Bits,L-Mul MSE,L-Mul Time (ns),Mul MSE,Mul Time (ns),Time Reduction (%)" << endl;

    for (int mantissaBits = 2; mantissaBits <= 23; mantissaBits++) {
        float lMulMSE = 0;
        float mulMSE = 0;
        long long lMulTotalTime = 0;
        long long mulTotalTime = 0;

        for (int i = 0; i < N; i++) {
            auto start = high_resolution_clock::now();
            vector<float> similaritiesLMul = cosineSimilarity1D2D(v1, v2, mantissaBits, lMul);
            auto stop = high_resolution_clock::now();
            auto durationLMul = duration_cast<nanoseconds>(stop - start);

            start = high_resolution_clock::now();
            vector<float> similaritiesMul = cosineSimilarity1D2D(v1, v2, mantissaBits, mul);
            stop = high_resolution_clock::now();
            auto durationMul = duration_cast<nanoseconds>(stop - start);

            for (int j = 0; j < standardSimilarities.size(); j++) {
                lMulMSE += pow(similaritiesLMul[j] - standardSimilarities[j], 2);
                mulMSE += pow(similaritiesMul[j] - standardSimilarities[j], 2);
            }

            lMulTotalTime += durationLMul.count();
            mulTotalTime += durationMul.count();
        }

        lMulMSE /= (N * standardSimilarities.size());
        mulMSE /= (N * standardSimilarities.size());
        long long lMulAvgTime = lMulTotalTime / N;
        long long mulAvgTime = mulTotalTime / N;

        double timeReduction = (1.0 - static_cast<double>(lMulAvgTime) / mulAvgTime) * 100;

        cout << mantissaBits << "," << lMulMSE << "," << lMulAvgTime << "," << mulMSE << "," << mulAvgTime << "," << timeReduction << "%" << endl;
    }

    return 0;
}