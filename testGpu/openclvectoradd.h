#ifndef OPENCLVECTORADD_H
#define OPENCLVECTORADD_H

#include <QString>
#include <CL/cl.h>

class TestVector;

class OpenClVectorAdd
{
public:
    OpenClVectorAdd(const TestVector& testCase);
    ~OpenClVectorAdd();

    const QString& getCode() const;
    uint getNumDevices() const;
    uint getNumPlatforms() const;
    bool isDeviceId() const;
    bool isContext() const;
    bool isCommandQueue() const;
    bool isMemoryCreated() const;
    bool initailizeOpenClDataBuffers();
    bool buildOpenClKernel();
    bool setKernelArguments();
    bool executeTheKernelFunction();
    bool collectResult();

private:
    void init();
    cl_int createContext();
    cl_int createCommandQueue();
    cl_int initPlatformIds();
    cl_int initDeviceIds();
    bool createClMemoryObjects();

private:
    const TestVector& m_testCase;
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

    cl_program program{nullptr};
    cl_kernel kernel{nullptr};
    size_t global_item_size{0};
    size_t local_item_size{64};
};


#endif // OPENCLVECTORADD_H
