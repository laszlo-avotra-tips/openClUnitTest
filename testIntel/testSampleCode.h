#ifndef TESTSAMPLECODE_H
#define TESTSAMPLECODE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <CL/cl.h>
#include <openclsamplecode.h>

QString getReferenceCode();
QString getReferenceCode(){
const QString code{R"(__kernel void vector_add(__global const int *A, __global const int *B, __global int *C) {int i = get_global_id(0);C[i] = A[i] + B[i];})"};
return code;
}

using namespace testing;

TEST(sampleCode, case1)
{
    const int one{1};

    EXPECT_EQ(one, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(sampleCode, case2)
{
    OpenClSampleCode ut;

    EXPECT_EQ(1, ut.getNumDevices());
    EXPECT_EQ(2,ut.getNumPlatforms());
    EXPECT_EQ(getReferenceCode(), ut.getCode());
}


#endif // TESTSAMPLECODE_H
