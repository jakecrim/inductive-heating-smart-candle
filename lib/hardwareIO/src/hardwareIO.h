#ifndef hardwareIO
#define hardwareIO

/* INCLUDES */
#include <smartCandleSys.h>

/* DECLARATIONS */
void vHardwareInputsTask(void * parameter);
void gpioOpen(void);
void DDS_SetFreq();

// for communicating with the DDS
void send(unsigned long word);
void clock_tick();
void reset_tick();
void freq_update_tick();
unsigned long word_compute(unsigned long frequency);
void send_bit(int value);
void vHardwareOutputsTask(void * parameter);
void signalCoil(void);

/* DEFINES */
#define BUTTON1 33

#define PIN_DDS_RESET 11
#define PIN_DDS_DATA 10
#define PIN_DDS_FU_UD 9
#define PIN_DDS_W_CLK 8

#define PIN_COIL1 20
#define PIN_COIL2 21
#define COIL_WRITE_DELAY 100

#define PIN_LED LED_BUILTIN

#define DELAY_US 500

#define DDS_CLOCK 125000000

/* GLOBALS */
extern SemaphoreHandle_t sema_candle_state;
extern bool candle_state_on;
extern int coil_number_select;

#endif