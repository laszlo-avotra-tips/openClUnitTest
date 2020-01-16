#include "rescalekernel.h"

RescaleKernel::RescaleKernel()
{

}

void RescaleKernel::theFunction(const unsigned short *input,
                                float *output,
                                const float *fractionalSamples,
                                const float *wholeSamples,
                                const unsigned int inputLength,
                                const unsigned int outputLength)
{
    int i = 1;
    int j = 1;
    float interpSample;
    int write_offset = j * int(outputLength);
    int read_offset = j * int(inputLength);
    int input_pos;
    int sampleIndex;
    sampleIndex = int(wholeSamples[i]);

//    if ((sampleIndex + 1) > inputLength) {
//       return;
//    }

    input_pos = read_offset + sampleIndex;
    interpSample = float(input[input_pos + 1] - input[input_pos]) *
                       fractionalSamples[i];
    interpSample = interpSample + input[input_pos];

    // Apply the passed in window function and set the output
    output[i + write_offset] = interpSample;
}
