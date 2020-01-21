#ifndef TESTSAMPLECODE_H
#define TESTSAMPLECODE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <cudaWrapperL300.h>
#include <CL/cl.h>
#include <vectoraddtestvector.h>
#include <QDebug>
#include <QTime>
#include <cudaFFTwrapper.h>
#include <complex>


using Complex = std::complex<float>;
void addjustCoefficientMagnitude(Complex* h_data, long dataSize) noexcept;
int isOriginalEqualToTheTransformedAndInverseTransformenData(
    const Complex* original, const Complex* transformed, long dataSize) noexcept;
void printTheData(const Complex* original, const Complex* transformed, long dataSize, const int printOffset);
void initializeTheSignals(Complex* fft, Complex* invfft, long dataSize) noexcept;

void addjustCoefficientMagnitude(Complex* h_data, long dataSize) noexcept
{

    if (h_data) {
        for (long i = 0; i < dataSize; ++i) {
            h_data[i] = { h_data[i].real() / 8.0f / dataSize, 0 };
        }
    }
}

int isOriginalEqualToTheTransformedAndInverseTransformenData(
    const Complex* original, const Complex* transformed, long dataSize) noexcept
{
    int iTestResult = 1;
    if (original && transformed) {
        iTestResult = 0;
        for (int i = 0; i < dataSize; ++i) {
            if (std::abs(transformed[i].real() - original[i].real()) > abs(original[i].real() * 1e-4f))
                iTestResult += 1;
        }
    }
    return iTestResult;
}

void printTheData(const Complex* original, const Complex* transformed, long dataSize, const int printOffset)
{
    std::cout << "The first " << dataSize << " real values with offset [" << printOffset << "] :" << std::endl;
    if (original) {
        for (int i = 0; i < dataSize; ++i) {
            std::cout << original[i + printOffset].real() << " ";
        }
        std::cout << std::endl;
    }
    if (transformed) {
        for (int i = 0; i < dataSize; ++i) {
            std::cout << transformed[i + printOffset].real() << " ";
        }
        std::cout << std::endl;
    }
}

void initializeTheSignals(Complex* fft, Complex* invfft, long dataSize) noexcept
{
      for (long i = 0; i < dataSize; ++i) {
        if(fft){
            fft[i] = { rand() / static_cast<float>(RAND_MAX), 0 };
        }
        if(invfft){
            invfft[i] = { 0.1f };
        }
    }
}

using namespace testing;

TEST(unitTest, case1)
{
    const int one{1};

    EXPECT_EQ(one, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(testvector, case1)
{
    VectorAddTestVector v;

    ASSERT_EQ(VectorAddTestVector::LIST_SIZE, 1024);

    ASSERT_EQ(v.A[0], 0);
    ASSERT_EQ(v.A[14], 14);

    ASSERT_EQ(v.A[v.LIST_SIZE - 1], v.LIST_SIZE-1);
    ASSERT_EQ(v.B[v.LIST_SIZE - 14], 14);

}

TEST(cudaWrapper, case1)
{
    const size_t size{5};
    const int a[5] = {1,2,3,4,5};
    const int b[5] = {11,22,33,44,55};
    int c[5]{};

    QTime t1;
    t1.start();
    const bool isResultSuccess{addTwoVectors(c, a, b, size)};
    qDebug() << "[..........] " << t1.elapsed() << " ms elapsed in CUDA case1";

    EXPECT_TRUE(isResultSuccess);

    qDebug() << "[----------] " << c[0] << ", " << c[1] << ", "<< c[2] << ", "<< c[3] << ", "<< c[4];
}

TEST(cudaWrapper, case2)
{
    VectorAddTestVector v;

    QTime t1;

    t1.start();
    const bool isResultSuccess{addTwoVectors(v.C, v.A, v.B, v.LIST_SIZE)};
    qDebug() << "[..........] " << t1.elapsed() << " ms elapsed in CUDA case 2";

    EXPECT_TRUE(isResultSuccess);
    EXPECT_TRUE(v.testResultOfOPenClVectorAdd());
}

TEST(vector, data) {
    std::vector<float> ut{1,2,3};
    const float* utReadOnly = ut.data();
    EXPECT_EQ(2,utReadOnly[1]);
    float* utRW = ut.data();
    utRW[1] = 12345;
    EXPECT_EQ(12345,utReadOnly[1]);
}

TEST(cuda, matrix4by4Add)
{
    int A[4][4];
    int B[4][4];
    int C[4][4]{};
    int result[4][4];

    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j){
           result[i][j] = 10*(i+1) + 100*(j+1);
           A[i][j] = (i+1)*(j+1) + i;
           B[i][j] = result[i][j] - A[i][j];
        }
    }

    ASSERT_EQ(C[2][3],0);

    matrix4by4Add(C,A,B);

    ASSERT_EQ(result[2][3], C[2][3]);

    for(int i=0; i<4; ++i){
        for(int j=0; j<4; ++j){
//           qDebug() << "[" << i << "," << j << "] R=" << result[i][j] <<
//           ", A=" << A[i][j] <<
//           ", B=" << B[i][j] <<
//           ", C=" << C[i][j];
            ASSERT_EQ(result[i][j], C[i][j]);
        }
    }

}


TEST(cudaFFT, computeTheFFT)
{
    constexpr long SIGNAL_SIZE(1024);
    constexpr int batch{4};

    // Allocate host memory for the signal
    auto h_signal = std::make_unique<std::complex<float>[]>(SIGNAL_SIZE);
    auto h_signal_fft_ifft = std::make_unique<std::complex<float>[]>(SIGNAL_SIZE);

    initializeTheSignals(h_signal.get(), h_signal_fft_ifft.get(), SIGNAL_SIZE);


    ComputeTheFFT(h_signal.get(), h_signal_fft_ifft.get(), SIGNAL_SIZE, batch);

    // check result
    int iTestResult = 1;

    //result scaling
    addjustCoefficientMagnitude(h_signal_fft_ifft.get(), SIGNAL_SIZE);

    iTestResult = isOriginalEqualToTheTransformedAndInverseTransformenData(h_signal.get(), h_signal_fft_ifft.get(), SIGNAL_SIZE);

    printTheData(h_signal.get(), h_signal_fft_ifft.get(), 8, 0);

    EXPECT_EQ(0, iTestResult);
}

#endif // TESTSAMPLECODE_H
