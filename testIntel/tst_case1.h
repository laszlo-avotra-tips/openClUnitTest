#ifndef TST_CASE1_H
#define TST_CASE1_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <CL/cl.h>
#include <openclsamplecode.h>

#include <stdio.h>
#include <stdlib.h>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <string>

#define MAX_SOURCE_SIZE (0x100000)

struct OpenClCode{

    OpenClCode(){
        init();
        createContext();
    }
    const QString& getCode() const{
        return m_code;
    }
    uint getNumDevices() const{
        return ret_num_devices;
    }
    uint getNumPlatforms() const{
        return ret_num_platforms;
    }

private:
    void init(){
        initPlatformIds();
        initDeviceIds();
    }
    cl_int createContext(){
        cl_int ret{0};
        context = clCreateContext(nullptr,1,&device_id,nullptr,nullptr,&ret);
        return ret;
    }

    cl_int initPlatformIds(){
        cl_int ret = clGetPlatformIDs(1,&platform_id, &ret_num_platforms);
        qDebug() << ret_num_platforms;
        return ret;
    }
    cl_int initDeviceIds(){
        cl_int ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
                                     &device_id, &ret_num_devices);
        qDebug() << ret_num_devices;
        return ret;
    }


private:
    cl_context context{nullptr};
    cl_platform_id platform_id = nullptr;
    cl_device_id device_id = nullptr;
    cl_uint ret_num_devices{0};
    cl_uint ret_num_platforms{};
    const QString m_code{R"(__kernel void vector_add(__global const int *A, __global const int *B, __global int *C) {int i = get_global_id(0);C[i] = A[i] + B[i];})"};
};

using namespace testing;

TEST(suite1, case1)
{
    const int one{1};

    EXPECT_EQ(one, 1);
    ASSERT_THAT(0, Eq(0));

    OpenClCode ut;

    qDebug() << ut.getCode();
    EXPECT_EQ(1, ut.getNumDevices());
    EXPECT_EQ(2,ut.getNumPlatforms());


}

//TEST(suite1, case2)
//{
//    OpenClSampleCode ut;

//    EXPECT_EQ(1, ut.getNumDevices());
//    EXPECT_EQ(2,ut.getNumPlatforms());
//}


#endif // TST_CASE1_H
