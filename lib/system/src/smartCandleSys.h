// System Header for any defines to be shared across all other parts of the system
//      such as the arduino header file

#ifndef smartCandleSys
#define smartCandleSys

/* INCLUDES */
#include <Arduino.h>

/* DECLARATIONS */
void vHardwareInputsTask(void * parameter);

/* DEFINES */
// task/thread related
#define PRESSURE_SENSE_STACK_SIZE 10000
#define WIRELESS_STACK_SIZE 10000
#define HARDWARE_INPUTS_STACK_SIZE 10000
#define HARDWARE_OUTPUTS_STACK_SIZE 10000

#define PRESSURE_SENSE_PRIORITY 5 
#define WIRELESS_PRIORITY 5 
#define HARDWARE_INPUTS_PRIORITY 5
#define HARDWARE_OUTPUTS_PRIORITY 5



#endif