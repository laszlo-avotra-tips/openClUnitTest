#include "testvector.h"
#include <QDebug>

TestVector::TestVector()
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

void TestVector::print()
{
    for(size_t i = 0; i < LIST_SIZE; i++)
    {
        qDebug() << A[i] << " " << B[i] << " " << C[i] << endl;
    }
}
