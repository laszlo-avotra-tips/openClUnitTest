#isEmpty(CUDA_DIR):CUDA_DIR=$$(CUDA_DIR)

#isEmpty(CUDA_DIR) {
#    message("set CUDA_DIR as environment variable or qmake variable to get rid of this message")
    CUDA_DIR = "C:\Users\lvincze\Documents\GitHub\cudaUnitTest\cudaWraperL300"
    CUDA_DIR1 = "C:\Users\lvincze\Documents\GitHub\cudaUnitTest\cudaFFT"
    CUDA_DIR2 = "C:\CUDA\lib\x64"
    CUDA_DIR3 = "C:\Users\lvincze\Documents\GitHub\bin\win64"
#}

INCLUDEPATH *= \
    $$CUDA_DIR1

INCLUDEPATH *= \
    $$CUDA_DIR/cudaWraperL300

LIBS += -L$$CUDA_DIR/x64/Debug -lcudaWraperL300
LIBS += -L$$CUDA_DIR3/Debug -lcudaFFT
LIBS += -L$$CUDA_DIR2 -lcudart -lcufft
