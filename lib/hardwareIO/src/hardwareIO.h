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
void printLCD(uint16_t data);

/* DEFINES */
#define BUTTON1 36

#define PIN_DDS_RESET 4 // 11
#define PIN_DDS_DATA 0  // 10
#define PIN_DDS_FU_UD 2  // 9
#define PIN_DDS_W_CLK 15 // 8

// #define PIN_COIL1 36
#define PIN_COIL1 32
// #define PIN_COIL2 39
#define PIN_COIL2 33
#define COIL_WRITE_DELAY 500

#define PIN_LED LED_BUILTIN

#define DELAY_US 500

#define DDS_CLOCK 125000000

/* GLOBALS */
extern SemaphoreHandle_t sema_candle_state;
extern bool candle_state_on;
extern int coil_number_select;

#endif