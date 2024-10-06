# inductive-heating-smart-candle
*senior capstone project code* 
- This project featured a 'smart candle' which used inductive heating via a two-stage coil system surrounding a candle, that had two metal rods seperated by an insulator.
- Heating was triggered via either a button on the candle itself, or from a simple companion ios app that sent a message to the ESP32 microcontroller to start or stop the candle melting.
- A 'full' candle (full of wax) when turned on would have melting only happening via the top metal rod, and the software would routinely check the weight of the wax via a capacitive pressure sensor that was developed by my electrical engineering student teammate.
- Once the candle had burned off enough of the wax, the software would switch which stage was heating.
- This project achieved a top down melting behavior more similar to a traditional candle, and provided a convinient way to turn melting on and off.