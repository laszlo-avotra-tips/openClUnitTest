#ifndef TESTSAMPLECODE_H
#define TESTSAMPLECODE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <cudaWrapperL300.h>
#include <CL/cl.h>
#include <vectoraddtestvector.h>
#include <rescalekernel.h>
#include <QDebug>
#include <QTime>


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

TEST(rescale, theKernelFunction)
{
    const unsigned short input[8]{1,2,3,4,5,6,7,8};
    float output[5]{};
    const float fractionalSamples[4]{1,2,3,4};
    const float wholeSamples[4]{1,2,3,4};
    const unsigned int inputLength{1};
    const unsigned int outputLength{1};

    EXPECT_EQ(0,output[2]);

    RescaleKernel::theFunction( input, output,
                                fractionalSamples,
                                wholeSamples,
                                inputLength,
                                outputLength);
    EXPECT_EQ(6,output[2]);
}

TEST(cudRescale, parameters)
{
    char buffer[80]{};
    char* errorMsg{buffer};
    unsigned short data[8]{1,2,3,4,5,6,7,8};
    float wholeSample[2]{};
    float output[8]{};

    bool success = cudaRescale(output,nullptr,0,nullptr,nullptr,errorMsg);
    EXPECT_FALSE(success);
    if(!success){
        EXPECT_STREQ("Invalid arguments",errorMsg);
    }

    success = cudaRescale(output,data,8,nullptr,nullptr,errorMsg);
    EXPECT_FALSE(success);
    if(!success){
        EXPECT_STREQ("Invalid arguments",errorMsg);
    }

    success = cudaRescale(output,data,8,wholeSample,nullptr,errorMsg);
    EXPECT_FALSE(success);
    if(!success){
        EXPECT_STREQ("Invalid arguments",errorMsg);
    }
    success = cudaRescale(output,data,8,nullptr,wholeSample,errorMsg);
    EXPECT_FALSE(success);
    if(!success){
        EXPECT_STREQ("Invalid arguments",errorMsg);
    }
}

TEST(cudaRescale, memoryAllocation)
{
    char buffer[80]{};
    char* errorMsg{buffer};

//    const size_t sizeOfData{5758976/2};
//    const size_t sizeOfTable{2048};
    const size_t sizeOfData{1024};
    const size_t sizeOfTable{1024};

    unsigned short data[sizeOfData]{1};
    float fracSamples[sizeOfTable]{1};
    float wholeSamples[sizeOfTable]{1};
    float output[sizeOfData]{};

    bool success = cudaRescale(output,data,sizeOfData,wholeSamples,fracSamples,errorMsg);
    EXPECT_TRUE(success);
    if(success){
        EXPECT_EQ(0,buffer[0]);
    } else {
        qDebug() << "{!!!!!!!!!!] " << QString(errorMsg);
    }
}

#endif // TESTSAMPLECODE_H
