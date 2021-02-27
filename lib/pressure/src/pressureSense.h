// All capacitive sensor circuit related 
#ifndef pressureSense
#define pressureSense

/* INCLUDES */
#include <smartCandleSys.h>
#include <Adafruit_ADS1015.h>

/* DECLARATIONS*/
void capacitiveRead(void);
void vPressureSenseTask(void * parameter);
void capacitiveOpen(void);

/* DEFINES */
#define ADC_CAP 34
#define SDA_1   21
#define SCL_1   22

#endif