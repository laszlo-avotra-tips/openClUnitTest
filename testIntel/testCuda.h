#ifndef TESTCUDA_H
#define TESTCUDA_H

#include <gtest/gtest.h>
#include <testvector.h>
#include <cudaWrapperL300.h>
#include <QDebug>
#include <QTime>


using namespace testing;

TEST(cudaWrapper, addVector)
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

TEST(cudaWrapper, addVector2)
{
    TestVector v;

    QTime t1;

    t1.start();
    const bool isResultSuccess{addTwoVectors(v.C, v.A, v.B, v.LIST_SIZE)};
    qDebug() << "[..........] " << t1.elapsed() << " ms elapsed in CUDA case 2";

    EXPECT_TRUE(isResultSuccess);
    EXPECT_TRUE(v.testResultOfVectorAdd());
}

#endif // TESTCUDA_H
