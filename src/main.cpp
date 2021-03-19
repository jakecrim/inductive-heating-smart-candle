// ************************************* //
//	    ~ Overview of system ~       	 //
//                                       //
// - One time setup functions are called,//
//   then the threads aka 'tasks' are    //
//   opened, see 'tasksOpen'. These tasks//
//   are the routines that handle all    //
//   the parts of the systems, so check  //
//   them out each to get a feel of how  //
//   the system is working.              //
// ************************************* //

#include <smartCandleSys.h> // overall system header
// Headers for specific functionality
#include <pressureSense.h>
#include <wireless.h>
#include <hardwareIO.h>

/* DECLARATIONS*/
void tasksOpen(void); // openFreeRTOS tasks

/* GLOBALS */



int main(void)
{
    // Open Serial for COMs and slight delay to allow for serial setup
    Serial.begin(115200);

    pinMode(23, OUTPUT);
    while(1)
    {
        digitalWrite(23, HIGH);
        delay(1000);
        digitalWrite(23, LOW);
        delay(1000);
    }
    delayMicroseconds(5);
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
        // Sits idle in here, as the threads or 'tasks' in the 'tasksOpen()' function do their routine things
        delay(1000);
    }

    return 0;
}

void tasksOpen()
{
    printf("Opening FreeRTOS Tasks: \n");

    // the first thing passed to xTaskCreate is the function name, see the indicated folders and files to find this function
    
    // Wireless Smart Tasks (see wireless folder)
    xTaskCreate(vWirelessMaintenanceTask, "Wireless Maintenance", WIRELESS_STACK_SIZE, NULL, WIRELESS_PRIORITY, NULL);
    // External Hardware Inputs (see hardwareIO folder)
    xTaskCreate(vHardwareInputsTask, "Hardware Inputs", HARDWARE_INPUTS_STACK_SIZE, NULL, HARDWARE_INPUTS_PRIORITY, NULL);
    // Feedback Loop Sensors (see pressure folder)
    xTaskCreate(vPressureSenseTask, "Pressure Sense", PRESSURE_SENSE_STACK_SIZE, NULL, PRESSURE_SENSE_PRIORITY, NULL);
    // Coil Switching Manage -> GPIO High/Low Control (see hardwareIO folder)  
    xTaskCreate(vHardwareOutputsTask, "Hardware Outputs", HARDWARE_OUTPUTS_STACK_SIZE, NULL, HARDWARE_OUTPUTS_PRIORITY, NULL);
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