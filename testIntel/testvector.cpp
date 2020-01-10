#include "testvector.h"
#include <QDebug>

TestVector::TestVector() :
    code{"__kernel void vector_add(__global const int *A, __global const int *B, __global int *C) {int i = get_global_id(0);C[i] = A[i] + B[i];}"}
{
    A = new int[LIST_SIZE];
    B = new int[LIST_SIZE];
    C = new int[LIST_SIZE];

    for(size_t i = 0; i < LIST_SIZE; i++) {
        A[i] = int(i);
        B[i] = int(LIST_SIZE - i);
        C[i] = 0;
    }
}

TestVector::~TestVector()
{
    delete [] A;
    delete [] B;
    delete [] C;
}

void TestVector::print() const
{
    for(size_t i = 0; i < LIST_SIZE; i++)
    {
        qDebug() << A[i] << " " << B[i] << " " << C[i] << endl;
    }
}

bool TestVector::testResultOfOPenClVectorAdd() const
{
    bool success{true};

    for(size_t i = 0; i < LIST_SIZE; i++)
    {
        success = success && (C[i] == LIST_SIZE);
    }

    if(!success){
        print();
    }
    return success;
}
