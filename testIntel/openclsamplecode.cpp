#include "openclsamplecode.h"

OpenClSampleCode::OpenClSampleCode()
{

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

void OpenClSampleCode::init(){
    initPlatformIds();
    initDeviceIds();
}
cl_int OpenClSampleCode::createContext(){
    cl_int ret{0};
    context = clCreateContext(nullptr,1,&device_id,nullptr,nullptr,&ret);
    return ret;
}

cl_int OpenClSampleCode::initPlatformIds(){
    cl_int ret = clGetPlatformIDs(1,&platform_id, &ret_num_platforms);
//        qDebug() << ret_num_platforms;
    return ret;
}
cl_int OpenClSampleCode::initDeviceIds(){
    cl_int ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
                                 &device_id, &ret_num_devices);
//        qDebug() << ret_num_devices;
    return ret;
}

