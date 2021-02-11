#include <Arduino.h>

/* DEFINES*/
#define DAC_C1 25
#define DAC_C2 26
#define ADC_CAP 34

/* DECLARATIONS*/
void simpleSinGenerator(void);
void capacitiveRead(void);

int main(void)
{
    Serial.begin(115200);
    delay(10);
    printf("Serial Opened, program starting: \n");

    int capacitiveRaw = 0;
    
    simpleSinGenerator();
    capacitiveRead();
    while(1)
    {
        printf("In loop: \n");
        // capacitiveRaw = analogRead(36);
        delay(1000);

    }
}

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

void capacitiveRead()
{
    uint16_t capacitive_raw = 0;
    while(1)
    {
        // 12 bit resolution, 4095 = 3.3V
        capacitive_raw = analogRead(ADC_CAP);
        printf("Raw analog value is: %d \n", capacitive_raw);
        delay(100);
    }
}

// only used to get to main, achieves a more normal looking program structure
void setup() 
{
    main();
}

void loop() 
{
    // should never enter...
    delay(1000);
}