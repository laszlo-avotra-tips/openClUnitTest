#ifndef TESTVECTOR_H
#define TESTVECTOR_H


class TestVector
{
public:
static const size_t LIST_SIZE{1024};
    int* A{nullptr};
    int* B{nullptr};
    int* C{nullptr};
    const char* code{nullptr};

    TestVector();
    ~TestVector();

    void print(void) const;
    bool testResultOfOPenClVectorAdd() const;
};

#endif // TESTVECTOR_H
