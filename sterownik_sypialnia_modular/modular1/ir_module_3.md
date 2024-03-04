//#define DECODE_DENON        // Includes Sharp
//#define DECODE_JVC
//#define DECODE_KASEIKYO
//#define DECODE_PANASONIC    // the same as DECODE_KASEIKYO
//#define DECODE_LG
//#define DECODE_NEC          // Includes Apple and Onkyo
//#define DECODE_SAMSUNG
//#define DECODE_SONY
//#define DECODE_RC5
//#define DECODE_RC6

//#define DECODE_BOSEWAVE
//#define DECODE_LEGO_PF
//#define DECODE_MAGIQUEST
//#define DECODE_WHYNTER

//#define DECODE_DISTANCE     // universal decoder for pulse distance protocols
//#define DECODE_HASH         // special decoder for all protocols

//#define DEBUG               // Activate this for lots of lovely debug output from the decoders.
//#define PINLED 13

#include <Arduino.h>
//#include <Adafruit_NeoPixel.h>

#include "PinDefinitionsAndMore.h" //Define macros for input and output pin etc.
#include <IRremote.hpp>

/*
Adafruit_NeoPixel strip = Adafruit_NeoPixel(120, PINLED, NEO_GRB + NEO_KHZ800);

void setup() {
    pinMode(3, OUTPUT);
    strip.begin();
    strip.setBrightness(100);
    strip.show(); // Initialize all pixels to 'off'
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}

*/


void IR_receive_function() {
    /*
     * Check if received data is available and if yes, try to decode it.
     * Decoded result is in the IrReceiver.decodedIRData structure.
     *
     * E.g. command is in IrReceiver.decodedIRData.command
     * address is in command is in IrReceiver.decodedIRData.address
     * and up to 32 bit raw data in IrReceiver.decodedIRData.decodedRawData
     */
    if (IrReceiver.decode()) {

        // Print a short summary of received data
        IrReceiver.printIRResultShort(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
            // We have an unknown protocol here, print more info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
        Serial.println();

        /*
         * !!!Important!!! Enable receiving of the next value,
         * since receiving has stopped after the end of the current received data packet.
         */
        IrReceiver.resume(); // Enable receiving of the next value

        /*
         * Finally, check the received data and perform actions according to the received command
         */
        if (IrReceiver.decodedIRData.command == 0x5E) {
            digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
        } else if (IrReceiver.decodedIRData.command == 0xC) {
            digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
        }
        else if (IrReceiver.decodedIRData.command == 0x4D) {
            strip.setBrightness(100);
        }
        else if (IrReceiver.decodedIRData.command == 0xD) {
            strip.setBrightness(0);
        }
        else if (IrReceiver.decodedIRData.command == 0x9) {
            colorWipe(strip.Color(255, 0, 0), 20); // Red
        }
        else if (IrReceiver.decodedIRData.command == 0x8) {
            colorWipe(strip.Color(0, 255, 0), 20); // Green
        }
        else if (IrReceiver.decodedIRData.command == 0x4A) {
            colorWipe(strip.Color(0, 0, 255), 20); // Blue
        }
        else if (IrReceiver.decodedIRData.command == 0x49) {
            rainbow(1);
        }
        else if (IrReceiver.decodedIRData.command == 0x52) {
            rainbowCycle(1);
        }
    }
}


void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
