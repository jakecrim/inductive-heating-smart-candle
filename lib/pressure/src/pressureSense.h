// All capacitive sensor circuit related 
#ifndef pressureSense
#define pressureSense

/* INCLUDES */
#include <smartCandleSys.h>

/* DECLARATIONS*/
uint16_t capacitiveRead(void);
void vPressureSenseTask(void * parameter);

/* DEFINES */
// pins
#define ADC_CAP 34
#define SDA_1   21
#define SCL_1   22

// switch coils if the analog reading is less than this value
#define COIL_SWITCH_THRESHOLD 3455
#define COIL_SWITCHBACK_THRESHOLD 3470
#endif