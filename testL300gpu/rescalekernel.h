#ifndef RESCALEKERNEL_H
#define RESCALEKERNEL_H


class RescaleKernel
{
public:
    RescaleKernel();
    static void theFunction(const unsigned short *input,
                     float *output,
                     const float *fractionalSamples,
                     const float *wholeSamples,
                     const float *window,
                     const unsigned int inputLength,
                     const unsigned int outputLength);
};

#endif // RESCALEKERNEL_H
