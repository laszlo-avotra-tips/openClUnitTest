isEmpty(STATIC_LIB_DIR):STATIC_LIB_DIR=$$(STATIC_LIB_DIR)

isEmpty(STATIC_LIB_DIR) {
    message("set STATIC_LIB_DIR as environment variable or qmake variable to get rid of this message")
    STATIC_LIB_DIR = C:/Users/laszlo/source/repos/cudaAccel
}

INCLUDEPATH *= \
    $$STATIC_LIB_DIR \
    $$STATIC_LIB_DIR/cudaAccel/include \

LIBS += -L$$STATIC_LIB_DIR/x64/Debug -lcudaAccel
