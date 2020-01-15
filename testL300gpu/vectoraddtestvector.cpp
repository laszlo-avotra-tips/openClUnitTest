#include "vectoraddtestvector.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

VectorAddTestVector::VectorAddTestVector()
{
    A = new int[LIST_SIZE];
    B = new int[LIST_SIZE];
    C = new int[LIST_SIZE];

    for(size_t i = 0; i < LIST_SIZE; i++) {
        A[i] = int(i);
        B[i] = int(LIST_SIZE - i);
        C[i] = 0;
    }

    QFile codeFile(":/openCl/sampleCode");
    codeFile.open(QIODevice::ReadOnly);
    QTextStream qts(&codeFile);

//    qDebug() << qts.readAll();
    m_theCode = qts.readAll().toStdString();
    code = m_theCode.c_str();

}

VectorAddTestVector::~VectorAddTestVector()
{
    delete [] A;
    delete [] B;
    delete [] C;
}

void VectorAddTestVector::print() const
{
    for(size_t i = 0; i < LIST_SIZE; i++)
    {
        qDebug() << A[i] << " " << B[i] << " " << C[i] << endl;
    }
}

bool VectorAddTestVector::testResultOfOPenClVectorAdd() const
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
