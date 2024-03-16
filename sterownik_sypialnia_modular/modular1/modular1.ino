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

#define pinR 9
#define pinG 10
#define pinB 11

//#define kanal kanaladc

//  !!! DODAC INTERRUPT NA PIN RX UARTA ??

Adafruit_NeoPixel strip = Adafruit_NeoPixel(300, PINLED1, NEO_GRB + NEO_KHZ800);
	
String odebraneDane = "";

void setup() {
  strip.begin();
  strip.setBrightness(1);
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200);

//attachInterrupt(digitalPinToInterrupt(pinIR), IR_receive_function, CHANGE);
  //pinMode(tvled, INPUT_PULLUP);

  //strip2.begin();
  //strip2.setBrightness(100);
  //strip2.show(); // Initialize all pixels to 'off'
//  pinMode(BUTTON, INPUT_PULLUP); // internal pull-up resistor
//  attachInterrupt (digitalPinToInterrupt (BUTTON), changeEffect, CHANGE); // pressed
  //attachInterrupt(0, changeEffect, CHANGE);


  //setAll(1, 1, 1);
  Serial.println("READY");
}



void loop() {

serial_read_if();


  }

bool break_rainbow = 0;

//do seriala dodano volatile, sprawdzic czy pomaga na wieszanie

volatile void serial_read_if(void){
 if(Serial.available() > 0) { //Czy Arduino odebrało dane
    //Jeśli tak, to odczytujemy je do znaku końca linii i zapisz w zmiennej odebraneDane
    odebraneDane = Serial.readStringUntil('\n'); 
    
    
    if (odebraneDane == "sufiton") strip.setBrightness(20);
    if (odebraneDane == "son") { strip.setBrightness(20); Serial.println("son (brightness 20)"); }
    if (odebraneDane == "sufitoff") strip.setBrightness(0);

    if (odebraneDane == "soff") { 
    strip.setBrightness(0); 
    Serial.println("soff (brightness 0)"); 
    }
    if (odebraneDane == "s0") setAll(1, 0, 0);
    if (odebraneDane == "s01") setbrightness(1);
    if (odebraneDane == "s02") setbrightness(2);
    if (odebraneDane == "s03") setbrightness(3);
    if (odebraneDane == "s04") setbrightness(4);
    if (odebraneDane == "s05") setbrightness(5);
    if (odebraneDane == "s06") setbrightness(6);
    if (odebraneDane == "s07") setbrightness(7);
    if (odebraneDane == "s08") setbrightness(8);
    if (odebraneDane == "s09") setbrightness(9);
    if (odebraneDane == "s1") setbrightness(10);
    if (odebraneDane == "s2") setbrightness(20);
    if (odebraneDane == "s3") setbrightness(30);
    if (odebraneDane == "s4") setbrightness(40);
    if (odebraneDane == "s5") setbrightness(50);
    if (odebraneDane == "s6") setbrightness(60);
    //if (odebraneDane == "s6") strip.setBrightness(60);
    if (odebraneDane == "s7") setbrightness(70);
    if (odebraneDane == "s8") setbrightness(80);
    if (odebraneDane == "s9") setbrightness(90);
    if (odebraneDane == "s10") setbrightness(100);
    if (odebraneDane == "sufitfull") strip.setBrightness(100);

    if (odebraneDane == "tvoff") analogWrite(tvled, 0);
    if (odebraneDane == "tv0") analogWrite(tvled, 0);
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
    if (odebraneDane == "tvfull") analogWrite(tvled, 100);

    if (odebraneDane == "break") break_rainbow = 1;


    if (odebraneDane == "magenta") { setAll(100, 0, 255); Serial.println("magenta color"); }
    if (odebraneDane == "m1") { setAll(100, 0, 255); Serial.println("magenta color"); }
    if (odebraneDane == "m2") { setAll(125, 0, 255); Serial.println("magenta 2 color"); }
    if (odebraneDane == "m3") { setAll(155, 0, 255); Serial.println("magenta 3 color"); }
    if (odebraneDane == "p1") { setAll(255, 0, 255); Serial.println("pink 1"); }
    if (odebraneDane == "p2") { setAll(255, 0, 235); Serial.println("pink 2"); }
    if (odebraneDane == "p3") { setAll(255, 0, 215); Serial.println("pink 3"); }
    if (odebraneDane == "p4") { setAll(255, 0, 185); Serial.println("pink 4"); }
    if (odebraneDane == "p5") { setAll(255, 0, 135); Serial.println("pink 5"); }

    if (odebraneDane == "white") { setAll(255, 255, 200); 
    Serial.println("warm white"); }
    if (odebraneDane == "whitec") { setAll(255, 255, 255); 
    Serial.println("cold white"); }

    if (odebraneDane == "rainbow") { rainbow(50); Serial.println("rainbow"); }
    //if (odebraneDane == "r") { rainbow(50); Serial.println("rainbow"); }


    //kod ponizej wieszal serial
    /* albo problem s serial printem - on blokuje prawdopodobnie
    albo problem z brakiem delaya po ustawieniu jasnosci
    albo problem ze funkcje nie sa w oddzielnym pliku a zmienna nie jest global?
    zapelnia sie bufor seriala tez, warunek ifa w serial read tez moze blokowac


    
    /*

    //if (odebraneDane == "r01") { setbrightness(1); rainbow(50); Serial.println("rainbow r01"); }
    if (odebraneDane == "r02") { 
    setbrightness(2); 
    
    rainbow(50);
    Serial.println("rainbow r02"); }

    if (odebraneDane == "r03") { 
    setbrightness(3); 
    rainbow(50); 
    Serial.println("rainbow r03"); }

    if (odebraneDane == "r04") { 
    setbrightness(4); 
    rainbow(50); 
    Serial.println("rainbow r04"); }

    if (odebraneDane == "r05") { 
    setbrightness(5); 
    rainbow(50); 
    Serial.println("rainbow r05"); }

    if (odebraneDane == "r06") { setbrightness(6); 
    rainbow(50); 
    Serial.println("rainbow r06"); }
    //if (odebraneDane == "r07") { setbrightness(7); rainbow(50); Serial.println("rainbow r07"); }
    //if (odebraneDane == "r08") { setbrightness(8); rainbow(50); Serial.println("rainbow r08"); }
    //if (odebraneDane == "r09") { setbrightness(9); rainbow(50); Serial.println("rainbow r09"); }
    //if (odebraneDane == "r1") { setbrightness(10); rainbow(50); Serial.println("rainbow r10"); }
    //if (odebraneDane == "r15") { setbrightness(15); rainbow(50); Serial.println("rainbow r15"); }
    //if (odebraneDane == "r20") { setbrightness(20); rainbow(50); Serial.println("rainbow r20"); }
    //if (odebraneDane == "r40") { setbrightness(40); rainbow(50); Serial.println("rainbow r40"); }
    //if (odebraneDane == "r50") { setbrightness(50); rainbow(50); Serial.println("rainbow r50"); }
    //if (odebraneDane == "r100") { setbrightness(100); rainbow(50); Serial.println("rainbow r100"); }
    
    */


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