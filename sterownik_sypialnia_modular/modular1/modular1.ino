#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include "PinDefinitionsAndMore.h" //Define macros for input and output pin etc.
#include <IRremote.hpp>



#define PINLED1 13
#define NUM_LEDS 300
#define tvled 6
#define pinIR 2

//#define kanal kanaladc

Adafruit_NeoPixel strip = Adafruit_NeoPixel(300, PINLED1, NEO_GRB + NEO_KHZ800);
	
String odebraneDane = "";

void setup() {
  strip.begin();
  strip.setBrightness(0);
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(pinIR), IR_receive_function, CHANGE);

  //strip2.begin();
  //strip2.setBrightness(100);
  //strip2.show(); // Initialize all pixels to 'off'
//  pinMode(BUTTON, INPUT_PULLUP); // internal pull-up resistor
//  attachInterrupt (digitalPinToInterrupt (BUTTON), changeEffect, CHANGE); // pressed
  //attachInterrupt(0, changeEffect, CHANGE);
}



void loop() {




  }


void serial_read_if(void){
 if(Serial.available() > 0) { //Czy Arduino odebrało dane
    //Jeśli tak, to odczytujemy je do znaku końca linii i zapisz w zmiennej odebraneDane
    odebraneDane = Serial.readStringUntil('\n'); 
    
    if (odebraneDane == "sufiton") strip.setBrightness(20);
    if (odebraneDane == "s1") strip.setBrightness(10);
    if (odebraneDane == "s2") strip.setBrightness(20);
    if (odebraneDane == "s3") strip.setBrightness(30);
    if (odebraneDane == "s4") strip.setBrightness(40);
    if (odebraneDane == "s5") strip.setBrightness(50);
    if (odebraneDane == "s6") strip.setBrightness(60);
    if (odebraneDane == "s7") strip.setBrightness(70);
    if (odebraneDane == "s8") strip.setBrightness(80);
    if (odebraneDane == "s9") strip.setBrightness(90);
    if (odebraneDane == "s10") strip.setBrightness(100);
    if (odebraneDane == "s0") strip.setBrightness(0);
    if (odebraneDane == "sufitoff") strip.setBrightness(0);

    if (odebraneDane == "tv0") analogWrite(czerwona, 0);
    if (odebraneDane == "tv1") analogWrite(tvled, 10);
    if (odebraneDane == "tv2") analogWrite(tvled, 20);
    if (odebraneDane == "tv3") analogWrite(tvled, 30);
    if (odebraneDane == "tv4") analogWrite(tvled, 40);
    if (odebraneDane == "tv5") analogWrite(tvled, 50);
    if (odebraneDane == "tv6") analogWrite(tvled, 60);
    if (odebraneDane == "tv7") analogWrite(tvled, 70);
    if (odebraneDane == "tv8") analogWrite(tvled, 80);
    if (odebraneDane == "tv9") analogWrite(tvled, 90);
    if (odebraneDane == "tv10") analogWrite(tvled, 100);
    if (odebraneDane == "tvoff") analogWrite(tvled, (0);
    if (odebraneDane == "tvfull") analogWrite(tvled, (100);


    if (odebraneDane == "tvon") {
      digitalWrite(tvled, HIGH);
    }

    if (odebraneDane == "tvoff") {
      digitalWrite(tvled, LOW); 
    }

    if (odebraneDane == "temp") {
      digitalWrite(tvled, LOW); 
    }

    if (odebraneDane == "lcd1on") {
      digitalWrite(tvled, LOW); 
    }

    if (odebraneDane == "lcd1off") {
      digitalWrite(tvled, LOW); 
    }

  }
}





//pomyslec nad przeniesieniem do oddzielnego .ino lub .cpp

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
        //    digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
        } else if (IrReceiver.decodedIRData.command == 0xC) {
        //    digitalWrite(3, LOW);    // turn the LED off by making the voltage LOW
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