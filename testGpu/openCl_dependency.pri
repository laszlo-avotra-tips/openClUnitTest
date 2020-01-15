isEmpty(OPENCL_DIR):OPENCL_DIR=$$(OPENCL_DIR)

isEmpty(OPENCL_DIR) {
    message("set OPENCL_DIR as environment variable or qmake variable to get rid of this message")
    OPENCL_DIR = "C:/Program Files (x86)/IntelSWTools/sw_dev_tools/OpenCL/sdk"
}

INCLUDEPATH *= \
    $$OPENCL_DIR \
    $$OPENCL_DIR/include \

LIBS += -L$$OPENCL_DIR/lib/x64 -lopencl
