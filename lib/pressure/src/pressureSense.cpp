#include "pressureSense.h"
#include "hardwareIO.h"

/* GLOBALS */
// Adafruit_ADS1115 adc_chip1;



// polls the capacitive circuit to check if the pressure has dropped enough to switch coils
void vPressureSenseTask(void * parameter)
{
    uint16_t capacitive_averaged = 0;
    uint16_t threshold_reached_count = 0;
    uint16_t threshold_switchback_count = 0;

    for(;;)
    {
        capacitive_averaged = capacitiveRead();
        printf("Capacitive Avg: %d \n", capacitive_averaged);
        printLCD(capacitive_averaged);

        // Decide which Coil to select for heating, based on the current analog reading
        //  from the capacitive sensor circuit
        if(capacitive_averaged <= COIL_SWITCH_THRESHOLD)
        {
            // in case of outlier values, or moving of the candle shell, wait for 
            //    five averaged readings to be below or above the thresholds.
            threshold_reached_count++;
            if(threshold_reached_count > 5)
            {
                coil_number_select = 2;
                threshold_reached_count = 0;
            }
        }
        else if(capacitive_averaged > COIL_SWITCHBACK_THRESHOLD)
        {
            threshold_switchback_count++;
            if(threshold_switchback_count > 5)
            {
                coil_number_select = 2;
                threshold_switchback_count = 0;
            }
        }

		vTaskDelay(250 / portTICK_PERIOD_MS);
    }
}


uint16_t capacitiveRead()
{
    uint32_t capacitive_raw_sum = 0;
    uint32_t capacitive_raw_avg = 0;

    // *UNUSED* reading from the new adaChip
    // capacitive_raw = adc_chip1.readADC_SingleEnded(0);


    // average 10 sets of 100 ADC reads (also averaged) and return this average analog value from the past ~1.1 seconds 
    for(int l = 0; l < 10; l++)
    {
        for(int i = 0; i < 100; i++)
        {
            capacitive_raw_sum += analogRead(ADC_CAP);
            delayMicroseconds(10);
        }
        capacitive_raw_avg += capacitive_raw_sum / 100;
        capacitive_raw_sum = 0;
        delay(100);
    }

    capacitive_raw_avg = capacitive_raw_avg / 10;

    return capacitive_raw_avg;
}

