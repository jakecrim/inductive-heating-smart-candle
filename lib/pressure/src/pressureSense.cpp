#include "pressureSense.h"
#include "hardwareIO.h"

/* GLOBALS */
Adafruit_ADS1115 adc_chip1;


uint16_t capacitiveRead()
{
    uint16_t capacitive_raw = 0;

    // reading from the new adaChip
    capacitive_raw = adc_chip1.readADC_SingleEnded(0);

    // printf("Raw analog value is: %d \n", capacitive_raw);

    delay(25);

    return capacitive_raw;
}

// polls the capactive circuit to check if the pressure has dropped enough to switch coils
void vPressureSenseTask(void * parameter)
{
    uint16_t capacitive_raw = 0;
    for(;;)
    {
        capacitive_raw = capacitiveRead();
        printf("Capacitive Raw: %d \n", capacitive_raw);
        // switch coils if true
        if(capacitive_raw < COIL_SWITCH_THRESHOLD)
        {
            coil_number_select = 2;
        }
        if(capacitive_raw > 7600)
        {
            coil_number_select = 1;
        }
		vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}

void capactiveOpen()
{
    adc_chip1.begin();
}