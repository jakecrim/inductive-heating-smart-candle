// All capacitive sensor circuit related 
#ifndef pressureSense
#define pressureSense

#include <smartCandleSys.h>

/* DECLARATIONS*/
void capacitiveRead(void);
void vPressureSenseTask(void * parameter);

/* DEFINES */
#define ADC_CAP 34

#endif