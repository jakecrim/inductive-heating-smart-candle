#include "hardwareIO.h"

void vHardwareInputsTask(void * parameter)
{
    int button1Input = 0;
    int button2Input = 0;

    for(;;)
    {
        button1Input = digitalRead(BUTTON1);
        if(button1Input == 1)
        {
            printf("Button1 Press Detected:\n");
        }
        if(button2Input == 1)
        {
            printf("Button2 Press Detected:\n");
        }
        delay(50);
    }

}

void DDS_SetFreq()
{
    pinMode(PIN_DDS_RESET, OUTPUT);
    pinMode(PIN_DDS_DATA, OUTPUT);
    pinMode(PIN_DDS_FU_UD, OUTPUT);
    pinMode(PIN_DDS_W_CLK, OUTPUT);
    // pinMode(PIN_LED, OUTPUT);



    digitalWrite(PIN_DDS_RESET, LOW);
    digitalWrite(PIN_DDS_DATA, LOW);
    digitalWrite(PIN_DDS_FU_UD, LOW);
    digitalWrite(PIN_DDS_W_CLK, LOW);
    // digitalWrite(PIN_LED, LOW);

    Serial.write("DDS reset... ");
    reset_tick();
    Serial.write(" - Completed!\r\n");
    delay(1000);
    Serial.write("DDS reset... ");
    reset_tick();
    Serial.write(" - Completed!\r\n");
    send(0);
    delay(1000);

}

void gpioOpen()
{
    printf("|----------------------------|\n");
    printf("Opening Hardware IO Control \n");
    pinMode(BUTTON1, INPUT);

    // DDS Board Setup
    // pinMode(PIN_DDS_RESET, OUTPUT);
    // pinMode(PIN_DDS_DATA, OUTPUT);
    // pinMode(PIN_DDS_FU_UD, OUTPUT);
    // pinMode(PIN_DDS_W_CLK, OUTPUT);
    // pinMode(PIN_LED, OUTPUT);
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