#include "hardwareIO.h"
#include <LiquidCrystal_I2C.h>

/* GLOBALS */
SemaphoreHandle_t sema_candle_state;
bool candle_state_on;
int coil_number_select;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void vHardwareInputsTask(void * parameter)
{
    int button1Input = 0;
    int button2Input = 0;

    for(;;)
    {
        button1Input = digitalRead(BUTTON1);

        // ON/OFF button of candle
        // currently a polled solution, could be made into an interrupt based solution
        if(button1Input == 1)
        {
            printf("Candle ON Requested from external ON/OFF Button:\n");
        }
        // optional future input button for other functionality options
        if(button2Input == 1)
        {
            printf("Button2 Press Detected:\n");
        }
        vTaskDelay(40 / portTICK_PERIOD_MS);
    }

}

void vHardwareOutputsTask(void * parameter)
{
    candle_state_on = false;
    sema_candle_state = xSemaphoreCreateBinary();
    for(;;)
    {
        // candle_state_on is set to true at either:
        //     a. Hardware Button Input or 
        //     b. in wireless smart tasks where a message over Wi-Fi can request the candle ON
        if(candle_state_on == true)
        {
            // signalCoil();
        }
        digitalWrite(11, LOW);
        printf("HIGH: \n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        digitalWrite(11, LOW);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
        // Optional Code for if I decide a semaphore is a better solution for signaling
        // if(xSemaphoreTake(sema_candle_state, portMAX_DELAY) == pdPASS)
        // {
        //     printf("Candle Turning ON/OFF: \n");
        // }

        vTaskDelay(1500 / portTICK_PERIOD_MS);
    }
}

//  function for sending signal to correct coil circuit choice to turn ON/OFF
void signalCoil()
{
    if(coil_number_select == 1)
    {
        printf("Coil 1 On: \n");
        digitalWrite(PIN_COIL1, HIGH);
        vTaskDelay(COIL_WRITE_DELAY / portTICK_PERIOD_MS);
        digitalWrite(PIN_COIL1, LOW);
    }
    else if(coil_number_select == 2)
    {
        printf("Coil 2 On: \n");
        digitalWrite(PIN_COIL2, HIGH);
        vTaskDelay(COIL_WRITE_DELAY / portTICK_PERIOD_MS);
        digitalWrite(PIN_COIL2, LOW);
    }
}

// Sets the frequency of the DDS Function Generator Module to drive the capacitive circuit
void DDS_SetFreq()
{
    unsigned long freq_word;
    unsigned long converted_freq_word;

    // set pin directions
    pinMode(PIN_DDS_RESET, OUTPUT);
    pinMode(PIN_DDS_DATA, OUTPUT);
    pinMode(PIN_DDS_FU_UD, OUTPUT);
    pinMode(PIN_DDS_W_CLK, OUTPUT);
    // pinMode(PIN_LED, OUTPUT);

    // default pin output states
    digitalWrite(PIN_DDS_RESET, LOW);
    digitalWrite(PIN_DDS_DATA, LOW);
    digitalWrite(PIN_DDS_FU_UD, LOW);
    digitalWrite(PIN_DDS_W_CLK, LOW);
    // digitalWrite(PIN_LED, LOW); // unusued currently

    // to get the DDS up and running, reset twice, then 'send' any value, the DDS is now ready to
    //      receieve our desired operating frequency
    Serial.write("DDS reset... ");
    reset_tick();
    Serial.write(" - Completed!\r\n");
    delay(1000);
    Serial.write("DDS reset... ");
    reset_tick();
    Serial.write(" - Completed!\r\n");
    send(0);
    delay(1000);

    // Set Module to 100 Khz
    freq_word = 100000;
    converted_freq_word = word_compute(freq_word);
    send(converted_freq_word);
    delay(1000);
}

void gpioOpen()
{
    printf("|----------------------------|\n");
    printf("Opening Hardware IO Control \n");
    pinMode(BUTTON1, INPUT);
    pinMode(PIN_COIL1, OUTPUT);
    pinMode(PIN_COIL2, OUTPUT);
    pinMode(11, OUTPUT);

    // LCD Display Setup
    lcd.begin(16, 2);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("V1:");

    // by default use coil option '1'
    coil_number_select = 1;

}

void send(unsigned long word) {
    for(int i = 0; i < 32; i++) {
        // int val = word & 0b1;
        // Serial.write(val ? "1" : "0");
        // send_bit(val);
        send_bit(word & 0b1);
        // Serial.print("Value:");
        // Serial.println(val);
        word >>= 1;
    }

    // Control bits
    send_bit(0);
    send_bit(0);

    // Power-down
    send_bit(0);

    // Phase
    send_bit(0);
    send_bit(0);
    send_bit(0);
    send_bit(0);
    send_bit(0);
    
    freq_update_tick();
}

void send_bit(int value) {
    if(value)
        digitalWrite(PIN_DDS_DATA, HIGH);
    else
        digitalWrite(PIN_DDS_DATA, LOW);

    clock_tick();
}

void clock_tick() {
    delayMicroseconds(DELAY_US);
    digitalWrite(PIN_DDS_W_CLK, HIGH);
    delayMicroseconds(DELAY_US);
    digitalWrite(PIN_DDS_W_CLK, LOW);
}
void reset_tick() {
    digitalWrite(PIN_DDS_RESET, HIGH);
    delayMicroseconds(DELAY_US);
    digitalWrite(PIN_DDS_RESET, LOW);
    delayMicroseconds(DELAY_US);
}

void freq_update_tick() {
    digitalWrite(PIN_DDS_FU_UD, HIGH);
    delayMicroseconds(DELAY_US);
    delayMicroseconds(DELAY_US);
    digitalWrite(PIN_DDS_FU_UD, LOW);
}

unsigned long word_compute(unsigned long frequency) {
    return (4294967296 * frequency) / DDS_CLOCK;
}