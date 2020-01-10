#ifndef OPENCLSAMPLECODE_H
#define OPENCLSAMPLECODE_H

#include <QString>
#include <CL/cl.h>

class TestVector;

class OpenClSampleCode
{
public:
    OpenClSampleCode();
    const QString& getCode() const;
    uint getNumDevices() const;
    uint getNumPlatforms() const;
    bool isDeviceId() const;
    bool isContext() const;
    bool isCommandQueue() const;
    bool isMemoryCreated() const;
    bool initailizeData(const TestVector& data);
    bool buildOpenClKernel();
    bool setKernelArguments();
    bool executeTheKernelFunction();
    bool collectResult(TestVector& data);

private:
    void init();
    cl_int createContext();
    cl_int createCommandQueue();
    cl_int initPlatformIds();
    cl_int initDeviceIds();
    bool createClMemoryObjects();

private:
    cl_context context{nullptr};
    cl_command_queue command_queue{nullptr};
    cl_platform_id platform_id = nullptr;
    cl_device_id device_id = nullptr;
    cl_uint ret_num_devices{0};
    cl_uint ret_num_platforms{};
    const QString m_code;

    cl_mem a_mem_obj{nullptr};
    cl_mem b_mem_obj{nullptr};
    cl_mem c_mem_obj{nullptr};
    bool m_isMemoryCreated{false};

    cl_kernel kernel{nullptr};
    size_t global_item_size{0};
    size_t local_item_size{64};
};


#endif // OPENCLSAMPLECODE_H
