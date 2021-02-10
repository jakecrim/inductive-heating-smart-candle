#include <Arduino.h>

/* DEFINES*/
#define DAC_C1 25
#define DAC_C2 26

/* DECLARATIONS*/
void simpleSinGenerator(void);

int main(void)
{
    Serial.begin(115200);
    delay(10);
    printf("Serial Opened, program starting: \n");

    simpleSinGenerator();

    while(1)
    {
        printf("In loop: \n");
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