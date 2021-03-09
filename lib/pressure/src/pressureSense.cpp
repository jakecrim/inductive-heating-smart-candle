#include "pressureSense.h"

/* GLOBALS */
Adafruit_ADS1115 adc_chip1;


void capacitiveRead()
{
    uint16_t capacitive_raw = 0;

    // 12 bit resolution, 4095 = 3.3V
    capacitive_raw = analogRead(ADC_CAP);

    // reading from the new adaChip
    capacitive_raw = adc_chip1.readADC_SingleEnded(0);

    printf("Raw analog value is: %d \n", capacitive_raw);
    delay(25);
}

void vPressureSenseTask(void * parameter)
{
    for(;;)
    {
        capacitiveRead();
		vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}

void capactiveOpen()
{
    adc_chip1.begin();
}