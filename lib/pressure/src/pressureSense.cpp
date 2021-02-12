#include "pressureSense.h"

void capacitiveRead()
{
    uint16_t capacitive_raw = 0;

    // 12 bit resolution, 4095 = 3.3V
    capacitive_raw = analogRead(ADC_CAP);
    printf("Raw analog value is: %d \n", capacitive_raw);
    delay(25);
}

void vPressureSenseTask(void * parameter)
{
    for(;;)
    {
        capacitiveRead();
        delay(1000);
    }
}