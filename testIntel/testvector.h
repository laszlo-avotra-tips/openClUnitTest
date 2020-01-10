#ifndef TESTVECTOR_H
#define TESTVECTOR_H


class TestVector
{
public:
static const size_t LIST_SIZE{1024};
    int* A{nullptr};
    int* B{nullptr};
    int* C{nullptr};

    TestVector();
    void print(void);
};

#endif // TESTVECTOR_H
