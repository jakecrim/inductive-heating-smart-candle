#include "wireless.h"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <hardwareIO.h>

/* GLOBALS */
// const char * ssid = "jakey";
// const char * password = "12345678";
// const char * ssid = "Choma 5G";
// const char * password = "Kaiser99";
char ssid[] = "Choma 5G";
char pass[] = "Kaiser99";

// auth token for blynk servers
char auth[] = "6aW_cmjPMMIvBDqwQ20cJh3kkwYCj-7y";

void vWirelessMaintenanceTask(void * parameter)
{
    for(;;)
    {
        Blynk.run();
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

/* IOS APP BUTTON INPUT */
BLYNK_WRITE(V0)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    // You can also use:
    // String i = param.asStr();
    // double d = param.asDouble();

    // SOMEHOW signal to the hardware outputs task to power up coils
    xSemaphoreGive(sema_candle_state);
    if(pinValue == 1)
    {
        printf("Button ON Request from IOS App \n");
        candle_state_on = true;
    } 
    else
    {
        printf("Button OFF Request from IOS App \n");
        candle_state_on = false;
    }
}

BLYNK_WRITE(V1)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    // You can also use:
    // String i = param.asStr();
    // double d = param.asDouble();
    Serial.print("V1 Slider value is: ");
    Serial.println(pinValue);
}

BLYNK_WRITE(V3)
{
    int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
    // You can also use:
    // String i = param.asStr();
    // double d = param.asDouble();
    Serial.print("V3 Time value is: ");
    Serial.println(pinValue);
}

void wirelessOpen()
{
    printf("|----------------------------|\n");
    printf("Opening Wi-Fi Control\n");

    // Blynk Configures the Wi-Fi connection and authenticates with their servers for coms over the internet
    Blynk.begin(auth, ssid, pass);
}