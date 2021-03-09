#include <smartCandleSys.h> // overall system header
// Headers for specific functionality
#include <pressureSense.h>
#include <waveGen.h>
#include <wireless.h>
#include <hardwareIO.h>

/* DECLARATIONS*/
void tasksOpen(void); // openFreeRTOS tasks

/* GLOBALS */


int main(void)
{
    // Open Serial for COMs and slight delay to allow for serial setup
    Serial.begin(115200);
    delay(10);

    printf("Serial Opened, program starting: \n");

    // Configure the hardware inputs and outputs (push-buttons, gpio high/low for coil control)
    gpioOpen();

    // Set our Default Frequency for the DDS driving sin wave
    DDS_SetFreq();

    // Setup and Connect to Wi-Fi 
    wirelessOpen();
    // Open the main freeRTOS system tasks (threads)
    tasksOpen();

    while(1)
    {
        printf("In loop: \n");
        delay(1000);
    }

    return 0;
}

void tasksOpen()
{
    printf("Opening FreeRTOS Tasks: \n");
    
    // Wireless Smart Tasks
    xTaskCreate(vWirelessMaintenanceTask, "Wireless Maintenance", WIRELESS_STACK_SIZE, NULL, WIRELESS_PRIORITY, NULL);
    // Coil Switching Manage -> GPIO High/Low Control / External Hardware Inputs
    xTaskCreate(vHardwareInputsTask, "Hardware Inputs", HARDWARE_INPUTS_STACK_SIZE, NULL, HARDWARE_INPUTS_PRIORITY, NULL);
    // Feedback Loop Sensors
    xTaskCreate(vPressureSenseTask, "Pressure Sense", PRESSURE_SENSE_STACK_SIZE, NULL, PRESSURE_SENSE_PRIORITY, NULL);
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