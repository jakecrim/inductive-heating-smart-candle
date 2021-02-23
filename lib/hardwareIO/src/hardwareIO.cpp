#include "hardwareIO.h"

void vHardwareInputsTask(void * parameter)
{
    int button1Input = 0;
    int button2Input = 0;

    for(;;)
    {
        button1Input = digitalRead(BUTTON1);
        if(button1Input == 1)
        {
            printf("Button1 Press Detected:\n");
        }
        if(button2Input == 1)
        {
            printf("Button2 Press Detected:\n");
        }
        delay(50);
    }

}

void gpioOpen()
{
    printf("|----------------------------|\n");
    printf("Opening Hardware IO Control \n");
    pinMode(BUTTON1, INPUT);
}