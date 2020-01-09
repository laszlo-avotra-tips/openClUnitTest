#ifndef OPENCLSAMPLECODE_H
#define OPENCLSAMPLECODE_H

#include <QString>
#include <CL/cl.h>

class OpenClSampleCode
{
public:
    OpenClSampleCode();
    const QString& getCode() const;
    uint getNumDevices() const;
    uint getNumPlatforms() const;

private:
    void init();
    cl_int createContext();
    cl_int initPlatformIds();
    cl_int initDeviceIds();

private:
    cl_context context{nullptr};
    cl_platform_id platform_id = nullptr;
    cl_device_id device_id = nullptr;
    cl_uint ret_num_devices{0};
    cl_uint ret_num_platforms{};
    const QString m_code{R"(__kernel void vector_add(__global const int *A, __global const int *B, __global int *C) {int i = get_global_id(0);C[i] = A[i] + B[i];})"};
};


#endif // OPENCLSAMPLECODE_H
