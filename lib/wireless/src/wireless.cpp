#include "wireless.h"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

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
        delay(500);
    }

    // int connectionAttemptCount = 0;

    // for(;;)
    // {

    //     if(WiFi.status() == WL_CONNECTED)
    //         printf("WiFi Connected to: %s \n", ssid);
    //     else
    //     {
    //         printf("WiFi not connected: \n");
    //         connectionAttemptCount++;
    //         if(connectionAttemptCount > 20)
    //         {
    //             printf("Restarting to attempt Wi-Fi Connection:\n");
    //             delay(5000);
    //             ESP.restart();
    //         }
    //     }
    //     delay(10000);
    // }
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

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V0 Button value is: ");
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
    Blynk.begin(auth, ssid, pass);
    // WiFi.begin(ssid,password);
    // while(WiFi.status() != WL_CONNECTED)
    // {
    //     delay(250);
    //     printf("Attempting Wi-Fi Connection: \n");
    // }
    // printf("Connected to: %s \n", ssid);
}