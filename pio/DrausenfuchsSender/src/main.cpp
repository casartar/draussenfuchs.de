/*

Very basic 70cm-ISM fox-transmitter based on ESP32 and generic transmitter module.
See draussenfuchs.de for details.

--

The MIT License (MIT)

Copyright (c) 2025 Harm, DK4HAA, draussenfuchs.de

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

--

INSTALL

Install ESP32 via boards manager (if not done before)
  1. Open Arduino IDE
  2. Open Tools > Board > Boards Manager
  3. Search for "esp32"
  4. Install "esp32" by Espressif Systems

Select Board
  1. Select Tools > Board > esp32 > Nologo ESP32C3 Super Mini
  2. Use default settings for this board

Compile and install as usual. :)


IMPORTANT NOTE

This code uses deep sleep. Once flashed, your ESP32 will go
to deep sleep most of the time and will not be available as a serial
device during deep sleep.

You have to hold down the "boot" button and press the "RST" button
to go back into bootloader mode to re-flash/update the board.

*/

#include <Arduino.h>

#define SENDER 10

#if SENDER == 1
#define FREQ_HZ 440
#define NR_BEEP 1
#define TIME_TO_BEEP 200
#define TIME_BETWEEN_BEEP 100
#elif SENDER == 2
#define FREQ_HZ 440
#define NR_BEEP 2
#define TIME_TO_BEEP 100
#define TIME_BETWEEN_BEEP 100
#elif SENDER == 3
#define FREQ_HZ 440
#define NR_BEEP 3
#define TIME_TO_BEEP 66
#define TIME_BETWEEN_BEEP 100
#elif SENDER == 4
#define FREQ_HZ 880
#define NR_BEEP 1
#define TIME_TO_BEEP 200
#define TIME_BETWEEN_BEEP 100
#elif SENDER == 5
#define FREQ_HZ 880
#define NR_BEEP 2
#define TIME_TO_BEEP 100
#define TIME_BETWEEN_BEEP 100
#elif SENDER == 6
#define FREQ_HZ 880
#define NR_BEEP 3
#define TIME_TO_BEEP 66
#define TIME_BETWEEN_BEEP 100
#elif SENDER == 7
#define FREQ_HZ 1760
#define NR_BEEP 1
#define TIME_TO_BEEP 200
#define TIME_BETWEEN_BEEP 100
#elif SENDER == 8
#define FREQ_HZ 1760
#define NR_BEEP 2
#define TIME_TO_BEEP 100
#define TIME_BETWEEN_BEEP 100
#elif SENDER == 9
#define FREQ_HZ 1760
#define NR_BEEP 3
#define TIME_TO_BEEP 66
#define TIME_BETWEEN_BEEP 100
#elif SENDER == 10
#define FREQ_HZ 220
#define NR_BEEP 4
#define TIME_TO_BEEP 50
#define TIME_BETWEEN_BEEP 100
#else
#error "No node selected"
#endif

#define TIME_TO_SLEEP (((TIME_TO_BEEP * NR_BEEP) * 10) - (TIME_BETWEEN_BEEP * NR_BEEP))

#define DATA_PIN 3              // Pin of the ESP32 connected to the data pin of the transmitter module
#define TX_ARTIFICIAL_VCC_PIN 4 // Pin of the ESP32 providing power to the transmitter module due to unused enable pin

#define uS_TO_MS_FACTOR 1000 // Conversion factor for micro seconds to ms

void setup()
{
    // set pin modes
    pinMode(TX_ARTIFICIAL_VCC_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    // set wakeup timer
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_MS_FACTOR);

    for (size_t i = 0; i < NR_BEEP; i++)
    {
        // start TX
        digitalWrite(TX_ARTIFICIAL_VCC_PIN, HIGH); // enable transmitter module
        digitalWrite(LED_BUILTIN, LOW);            // enable built-in LED
        tone(DATA_PIN, FREQ_HZ);                   // output tone to transmitter
        delay(TIME_TO_BEEP);                       // wait...
        // stop TX
        noTone(DATA_PIN);                         // stop tone
        digitalWrite(LED_BUILTIN, HIGH);          // disable LED
        digitalWrite(TX_ARTIFICIAL_VCC_PIN, LOW); // disable transmitter module
                                                  // wait between beep
        delay(TIME_BETWEEN_BEEP);                 // wait...
    }

    esp_deep_sleep_start(); // go to deep sleep
}

void loop()
{
    // never executed because of deep sleep
}
