#include "wireless.h"
#include <WiFi.h>

// Globals
// const char * ssid = "jakey";
// const char * password = "12345678";
const char * ssid = "Choma 5G";
const char * password = "Kaiser99";

void vWirelessMaintenanceTask(void * parameter)
{
    int connectionAttemptCount = 0;

    for(;;)
    {

        if(WiFi.status() == WL_CONNECTED)
            printf("WiFi Connected to: %s \n", ssid);
        else
        {
            printf("WiFi not connected: \n");
            connectionAttemptCount++;
            if(connectionAttemptCount > 20)
            {
                printf("Restarting to attempt Wi-Fi Connection:\n");
                delay(5000);
                ESP.restart();
            }
        }
        delay(10000);
    }
}

void wirelessOpen()
{
    printf("|----------------------------|\n");
    printf("Opening Wi-Fi Control\n");
    WiFi.begin(ssid,password);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(250);
        printf("Attempting Wi-Fi Connection: \n");
    }
    printf("Connected to: %s \n", ssid);
}