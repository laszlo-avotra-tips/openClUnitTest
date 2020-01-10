#ifndef TESTSAMPLECODE_H
#define TESTSAMPLECODE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <CL/cl.h>
#include <openclsamplecode.h>
#include <testvector.h>

QString getReferenceCode();
QString getReferenceCode(){
const QString code{R"(__kernel void vector_add(__global const int *A, __global const int *B, __global int *C) {int i = get_global_id(0);C[i] = A[i] + B[i];})"};
return code;
}

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
    OpenClSampleCode ut;

    EXPECT_EQ(1, ut.getNumDevices());
    EXPECT_EQ(2,ut.getNumPlatforms());
    EXPECT_EQ(getReferenceCode(), ut.getCode());

    EXPECT_TRUE(ut.isDeviceId());
    EXPECT_TRUE(ut.isContext());
    EXPECT_TRUE(ut.isCommandQueue());
    EXPECT_TRUE(ut.isMemoryCreated());

    TestVector v;

    EXPECT_TRUE(ut.initailizeData(v));
    EXPECT_TRUE(ut.buildOpenClKernel());

    EXPECT_TRUE(ut.setKernelArguments());

    EXPECT_TRUE(ut.executeTheKernelFunction());

    EXPECT_TRUE(ut.collectResult(v));

    v.print();
}



#endif // TESTSAMPLECODE_H
