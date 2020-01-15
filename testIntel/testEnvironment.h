#ifndef TESTSAMPLECODE_H
#define TESTSAMPLECODE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <testvector.h>
#include <cudaAccel/framework.h>
#include <QDebug>
#include <QTime>


using namespace testing;

TEST(unitTest, libraries)
{
    const int one{1};

    EXPECT_EQ(one, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(testVector, vectorAdd)
{
    TestVector v;

    ASSERT_EQ(TestVector::LIST_SIZE, 1024);

    ASSERT_EQ(v.A[0], 0);
    ASSERT_EQ(v.A[14], 14);

    ASSERT_EQ(v.A[v.LIST_SIZE - 1], v.LIST_SIZE-1);
    ASSERT_EQ(v.B[v.LIST_SIZE - 14], 14);

}

TEST(cudaAccelLib, library)
{
    int a{7};
    int b{8};
    int c{0};

    addVector(&a, &b, &c);

    EXPECT_EQ(15,c);
}

TEST(vector, dataFunction) {
    std::vector<float> ut{1,2,3};
    const float* utReadOnly = ut.data();
    EXPECT_EQ(2,utReadOnly[1]);
    float* utRW = ut.data();
    utRW[1] = 12345;
    EXPECT_EQ(12345,utReadOnly[1]);
}

#endif // TESTSAMPLECODE_H
