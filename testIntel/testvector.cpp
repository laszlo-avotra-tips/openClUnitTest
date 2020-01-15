#include "testvector.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

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

    QFile codeFile(":/openCl/sampleCode");
    codeFile.open(QIODevice::ReadOnly);
    QTextStream qts(&codeFile);

//    qDebug() << qts.readAll();
    m_theCode = qts.readAll().toStdString();
    code = m_theCode.c_str();

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

bool TestVector::testResultOfVectorAdd() const
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
