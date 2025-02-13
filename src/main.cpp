#include <Arduino.h>
#include <Visualization.h>

/*
.                   ┌───────────────┐
.                   │0        VIN/5v│
.               LED-│1           GND│
.                   │2           3.3│
.                   │3            10│
.                   │4             9│
.                   │5             8│
.           Trigger-│6             7│
.                   └───────────────┘
*/

////////////////////////////////////////////////////////////////////////////////////////////////
// LEDS
////////////////////////////////////////////////////////////////////////////////////////////////
#define NUM_LEDS 100
#define ROWS 100
#define COLUMNS 1
#define DISPLAY_LED_PIN 7

uint_fast8_t saturation = 244;

CRGB leds[NUM_LEDS];
CRGB off;

Visualization * all;

int top = 0;
float topF = 0;

void setup() {
    while(!Serial && millis() < 10000);
    Serial.println("setup");

    FastLED.addLeds<WS2812B, DISPLAY_LED_PIN, RGB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );;
    all = new Visualization(COLUMNS, ROWS, 0, saturation, leds);
    all->setValue(32);

    all->setAllCRGB(0x0F0000);
    FastLED.show();
    delay(1500);
}

// eq-like visualization
void loop() {
    all->clearAll();  // clear leds

    // Analog read pin A6
    // 0 - 1023
    int velocity = analogRead(A6);

    int current = map(velocity, 100, 1023, 0, 100);

    if (current > top) {
        top = current;
        topF = top;
    } else {
        topF = topF * 0.95 ;
        top = (int)topF;
    }

    for(int i = 0; i < top; i++) {
        leds[i] = 0x00000F;
    }
    FastLED.show();
}

// void loop() {
//     all->clearAll();  // clear leds

//     // Analog read pin A6
//     // 0 - 1023
//     int velocity = analogRead(A6);

//     int current = map(velocity, 200, 1023, 0, 255);

//     if (current > top && current > 1) {
//         top = current;
//         topF = top;
//     } else {
//         topF = topF * 0.8 ;
//         top = (int)topF;
//         top = 0;
//     }

//     for(int i = 0; i < NUM_LEDS; i++) {
//         leds[i] = CHSV(244, saturation, top);
//     }
//     FastLED.show();
// }