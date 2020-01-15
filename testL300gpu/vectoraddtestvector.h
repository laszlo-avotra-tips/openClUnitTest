#ifndef VECTORADDTESTVECTOR_H
#define VECTORADDTESTVECTOR_H

#include <string>

class VectorAddTestVector
{
public:
static const size_t LIST_SIZE{1024};
    int* A{nullptr};
    int* B{nullptr};
    int* C{nullptr};
    const char* code{nullptr};

    VectorAddTestVector();
    ~VectorAddTestVector();

    void print(void) const;
    bool testResultOfOPenClVectorAdd() const;

private:
    std::string m_theCode;
};

#endif // VECTORADDTESTVECTOR_H
