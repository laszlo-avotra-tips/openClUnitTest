#ifndef TESTSAMPLECODE_H
#define TESTSAMPLECODE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <CL/cl.h>
#include <openclsamplecode.h>
#include <testvector.h>
#include <cudaAccel/framework.h>
#include <cudaWrapperL300.h>
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
    TestVector v;

    ASSERT_EQ(TestVector::LIST_SIZE, 1024);

    ASSERT_EQ(v.A[0], 0);
    ASSERT_EQ(v.A[14], 14);

    ASSERT_EQ(v.A[v.LIST_SIZE - 1], v.LIST_SIZE-1);
    ASSERT_EQ(v.B[v.LIST_SIZE - 14], 14);

}

TEST(sampleCode, case2)
{
    TestVector v;
    OpenClSampleCode ut(v);

    QTime t1;
    t1.start();

    EXPECT_EQ(1, ut.getNumDevices());
    EXPECT_EQ(2,ut.getNumPlatforms());
    EXPECT_EQ(QString(v.code), ut.getCode());

    EXPECT_TRUE(ut.isDeviceId());
    EXPECT_TRUE(ut.isContext());
    EXPECT_TRUE(ut.isCommandQueue());
    EXPECT_TRUE(ut.isMemoryCreated());


    EXPECT_TRUE(ut.initailizeOpenClDataBuffers());
    EXPECT_TRUE(ut.buildOpenClKernel());
    EXPECT_TRUE(ut.setKernelArguments());
    EXPECT_TRUE(ut.executeTheKernelFunction());
    const bool isResultSuccess{ut.collectResult()};
    qDebug() << "[..........] " << t1.elapsed() << " ms elapsed in openCl";

    EXPECT_TRUE(isResultSuccess);

    EXPECT_TRUE(v.testResultOfOPenClVectorAdd());

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
    TestVector v;

    QTime t1;

    t1.start();
    const bool isResultSuccess{addTwoVectors(v.C, v.A, v.B, v.LIST_SIZE)};
    qDebug() << "[..........] " << t1.elapsed() << " ms elapsed in CUDA case 2";

    EXPECT_TRUE(isResultSuccess);
    EXPECT_TRUE(v.testResultOfOPenClVectorAdd());
}

TEST(cudaAccelLib, case1)
{
    int a{7};
    int b{8};
    int c{0};

    addVector(&a, &b, &c);

    EXPECT_EQ(15,c);
}

TEST(vector, data) {
    std::vector<float> ut{1,2,3};
    const float* utReadOnly = ut.data();
    EXPECT_EQ(2,utReadOnly[1]);
    float* utRW = ut.data();
    utRW[1] = 12345;
    EXPECT_EQ(12345,utReadOnly[1]);
}

#endif // TESTSAMPLECODE_H
