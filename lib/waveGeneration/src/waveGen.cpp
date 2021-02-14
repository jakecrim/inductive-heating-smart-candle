#include "waveGen.h"

void simpleSinGenerator()
{
    int freqMultiplier = 1;
    while(1)
    {
        // 128 gets to 'center of  range' :                 + 8 will make it ~1.25khz
        for(int degree = 0; degree < 360; degree = degree + 1) // ~126 hz
        {
            //                 offset  amp       freq               
            dacWrite(DAC_C1, int(128 + 64 * sin(freqMultiplier * degree * PI / 180)));
        }
    }
}

void complexSinGenerator()
{  
    printf("Test \n");
}