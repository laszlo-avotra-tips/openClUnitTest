#ifndef TESTSOPENCL_H
#define TESTSOPENCL_H

#include <gtest/gtest.h>
#include <CL/cl.h>
#include <openclvectoradd.h>
#include <testvector.h>
#include <QDebug>
#include <QTime>

using namespace testing;


TEST(openClVectorAdd, Intel)
{
    TestVector v;
    OpenClVectorAdd ut(v);

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

    EXPECT_TRUE(v.testResultOfVectorAdd());

}

#endif // TESTSOPENCL_H
