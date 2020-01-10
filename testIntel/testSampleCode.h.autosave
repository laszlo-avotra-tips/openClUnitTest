#ifndef TESTSAMPLECODE_H
#define TESTSAMPLECODE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <CL/cl.h>
#include <openclsamplecode.h>
#include <testvector.h>


using namespace testing;

TEST(unitTest, case1)
{
    const int one{1};

    EXPECT_EQ(one, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(vector, case1)
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
    EXPECT_TRUE(ut.collectResult());
    EXPECT_TRUE(v.testResultOfOPenClVectorAdd());
}



#endif // TESTSAMPLECODE_H
