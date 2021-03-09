#ifndef wireless
#define wireless

/* INCLUDES */
#include <smartCandleSys.h>

/* DEFINES*/
#define BLYNK_PRINT Serial

/* DECLARATIONS */
void wirelessOpen(void);
void vWirelessMaintenanceTask(void * parameter);

#endif