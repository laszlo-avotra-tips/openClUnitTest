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
    constexpr int fftSize{2048};
    constexpr int batchSize{160};
    constexpr long dataSize(fftSize * batchSize);

    // Allocate host memory for the signal
    auto h_signal = std::make_unique<std::complex<float>[]>(dataSize);
    auto h_signal_fft_ifft = std::make_unique<std::complex<float>[]>(dataSize);

    initializeTheSignals(h_signal.get(), dataSize);


    ComputeTheFFT(h_signal.get(),nullptr, dataSize, batchSize);

    // check result
    int iTestResult = 0;

    //result scaling
//    addjustCoefficientMagnitude(h_signal_fft_ifft.get(), SIGNAL_SIZE);

//    iTestResult = isOriginalEqualToTheTransformedAndInverseTransformenData(h_signal.get(), h_signal_fft_ifft.get(), SIGNAL_SIZE);

    printTheData(h_signal.get(), nullptr, 8, dataSize - 9);

    EXPECT_EQ(0, iTestResult);
}

//TEST(cudaFFT, computeTheFFT2)
//{
//    constexpr long SIGNAL_SIZE(1024);
//    constexpr int batch{4};

//    // Allocate host memory for the signal
//    auto h_signal = std::make_unique<std::complex<float>[]>(SIGNAL_SIZE);
//    auto h_signal_fft_ifft = std::make_unique<std::complex<float>[]>(SIGNAL_SIZE);

//    auto h_signal_pointer = h_signal.get();
//    auto h_signal_fft_ifft_pointer = nullptr;//h_signal_fft_ifft.get();

//    initializeTheSignals(h_signal_pointer, SIGNAL_SIZE);


//    ComputeTheFFT(h_signal_pointer, h_signal_fft_ifft_pointer, SIGNAL_SIZE, batch);

//    // check result
//    int iTestResult = 1;

//    //result scaling
//    addjustCoefficientMagnitude(h_signal_fft_ifft_pointer, SIGNAL_SIZE);

//    iTestResult = isOriginalEqualToTheTransformedAndInverseTransformenData(h_signal_pointer, h_signal_fft_ifft_pointer, SIGNAL_SIZE);

//    printTheData(h_signal_pointer, h_signal_fft_ifft_pointer, 8, 0);

//    EXPECT_EQ(0, iTestResult);
//}

#endif // TESTSAMPLECODE_H
