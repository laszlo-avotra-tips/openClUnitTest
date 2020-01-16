#ifndef TESTSAMPLECODE_H
#define TESTSAMPLECODE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <testvector.h>
//#include <cudaAccel/framework.h>
#include <QDebug>
#include <QTime>


using namespace testing;

#define ADD_COLUMN_COUNT 3

void add(int c[][ADD_COLUMN_COUNT], const int a[][ADD_COLUMN_COUNT], const int b[][ADD_COLUMN_COUNT], const size_t N=ADD_COLUMN_COUNT);

void add(int c[][ADD_COLUMN_COUNT], const int a[][ADD_COLUMN_COUNT], const int b[][ADD_COLUMN_COUNT], const size_t N){
    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j < N; ++j){
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}


TEST(unitTest, libraries)
{
    const int one{1};

    EXPECT_EQ(one, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(c,array)
{
    int a[3][3] = {{11,12,13},{21,22,23},{31,32,33}};
    int b[3][3] = {{111,112,113},{121,122,123},{131,132,133}};
    int c[3][3] = {};

    ASSERT_EQ(a[0][0],11);
    ASSERT_EQ(a[1][2],23);
    ASSERT_EQ(a[2][2],33);

    ASSERT_EQ(c[0][0],0);

    add(c,a,b,3);

    ASSERT_EQ(c[0][0],122);

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

//TEST(cudaAccelLib, library)
//{
//    int a{7};
//    int b{8};
//    int c{0};

//    addVector(&a, &b, &c);

//    EXPECT_EQ(15,c);
//}

TEST(vector, dataFunction) {
    std::vector<float> ut{1,2,3};
    const float* utReadOnly = ut.data();
    EXPECT_EQ(2,utReadOnly[1]);
    float* utRW = ut.data();
    utRW[1] = 12345;
    EXPECT_EQ(12345,utReadOnly[1]);
}

#endif // TESTSAMPLECODE_H
