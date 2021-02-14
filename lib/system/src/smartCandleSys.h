// System Header for any defines to be shared across all other parts of the system
//      such as the arduino header file

#ifndef smartCandleSys
#define smartCandleSys

/* DECLARATIONS */
#include <Arduino.h>

/* DEFINES */
// task/thread related
#define PRESSURE_SENSE_STACK_SIZE 10000
#define WIRELESS_STACK_SIZE 10000

#define PRESSURE_SENSE_PRIORITY 5 
#define WIRELESS_PRIORITY 5 



#endif