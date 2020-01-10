#include "openclsamplecode.h"
#include <testvector.h>

#include <QDebug>

OpenClSampleCode::OpenClSampleCode() : m_code{"__kernel void vector_add(__global const int *A, __global const int *B, __global int *C) {int i = get_global_id(0);C[i] = A[i] + B[i];}"}
{
    init();
    createContext();
    createCommandQueue();
    createClMemoryObjects();
}

const QString& OpenClSampleCode::getCode() const{
    return m_code;
}

uint OpenClSampleCode::getNumDevices() const{
    return ret_num_devices;
}
uint OpenClSampleCode::getNumPlatforms() const{
    return ret_num_platforms;
}

bool OpenClSampleCode::isDeviceId() const
{
    return device_id;
}

bool OpenClSampleCode::isContext() const
{
    return context;
}

bool OpenClSampleCode::isCommandQueue() const
{
    return command_queue;
}

bool OpenClSampleCode::isMemoryCreated() const
{
    return m_isMemoryCreated;
}

bool OpenClSampleCode::initailizeData(const TestVector &data)
{
    bool success{true};
    cl_int ret{0};

    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,
            TestVector::LIST_SIZE * sizeof(int), data.A, 0, nullptr, nullptr);
    success = success && !ret;

    ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,
            TestVector::LIST_SIZE * sizeof(int), data.B, 0, nullptr, nullptr);
    success = success && !ret;

    return success;
}

bool OpenClSampleCode::buildOpenClKernel()
{
    bool success{true};
    cl_int ret{0};

    // Create a program from the kernel source
    const QString& code{getCode()};
//    qDebug() << code;
    const auto stdSring{code.toStdString()};
    char const * src{stdSring.c_str()};
//    qDebug() << src;

    const size_t source_size = size_t(getCode().size());

    cl_program program = clCreateProgramWithSource(context, 1,
                                                   &src, &source_size, &ret);
    success = success && !ret;

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, nullptr, nullptr, nullptr);
    success = success && !ret;
    // Create the OpenCL kernel
    kernel = clCreateKernel(program, "vector_add", &ret);
    success = success && !ret && kernel;

    return success;
}

bool OpenClSampleCode::setKernelArguments()
{
    bool success{true};
    cl_int ret(0);

    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), static_cast<void *>(&a_mem_obj));
    success = success && !ret;
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), static_cast<void *>(&b_mem_obj));
    success = success && !ret;
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), static_cast<void *>(&c_mem_obj));
    success = success && !ret;

    global_item_size = TestVector::LIST_SIZE; // Process the entire lists
    local_item_size = 64; // Divide work items into groups of 64

    return success;
}

bool OpenClSampleCode::executeTheKernelFunction()
{
    cl_int ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, nullptr,
            &global_item_size, &local_item_size, 0, nullptr, nullptr);
    bool success = !ret;

    return success;
}

bool OpenClSampleCode::collectResult(TestVector &data)
{
    cl_int ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0,
            data.LIST_SIZE * sizeof(int), data.C, 0, nullptr, nullptr);
    return ret == CL_SUCCESS;
}

void OpenClSampleCode::init(){
    initPlatformIds();
    initDeviceIds();
}
cl_int OpenClSampleCode::createContext(){
    cl_int ret{0};
    context = clCreateContext(nullptr,1,&device_id,nullptr,nullptr,&ret);
    return ret;
}

cl_int OpenClSampleCode::createCommandQueue()
{
    cl_int ret{0};
//    command_queue = clCreateCommandQueue(context, device_id, 0, &ret); //lcv deprecated
    /* Create the command queue */
    //queue = clCreateCommandQueue(context, device_list[0], 0, &clStatus);
    command_queue = clCreateCommandQueueWithProperties(context, device_id, nullptr, &ret);
    return ret;
}

cl_int OpenClSampleCode::initPlatformIds(){

    cl_int err = clGetPlatformIDs(1,&platform_id, &ret_num_platforms);
    qDebug() << ret_num_platforms;

    const int DefaultStringSize = 128;
    char vendor[ DefaultStringSize ];
    char name[ DefaultStringSize ];
    char version[ DefaultStringSize ];

    err |= clGetPlatformInfo( platform_id, CL_PLATFORM_VENDOR,  DefaultStringSize, vendor,  nullptr );
    err |= clGetPlatformInfo( platform_id, CL_PLATFORM_NAME,    DefaultStringSize, name,    nullptr );
    err |= clGetPlatformInfo( platform_id, CL_PLATFORM_VERSION, DefaultStringSize, version, nullptr );

    qDebug() << "vendor " << vendor << ", name " << name << ", version " << version;

    return err;
}
cl_int OpenClSampleCode::initDeviceIds(){
    cl_int ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
                                 &device_id, &ret_num_devices);
//        qDebug() << ret_num_devices;
    return ret;
}

bool OpenClSampleCode::createClMemoryObjects()
{
    bool success{true};
    cl_int ret(0);

    a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
            TestVector::LIST_SIZE * sizeof(int), nullptr, &ret);
    success = success && !ret && a_mem_obj;

    b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
            TestVector::LIST_SIZE * sizeof(int), nullptr, &ret);
    success = success && !ret && b_mem_obj;

    c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
            TestVector::LIST_SIZE * sizeof(int), nullptr, &ret);
    success = success && !ret && c_mem_obj;

    m_isMemoryCreated = success;

    return m_isMemoryCreated;
}

