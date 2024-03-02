#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PINLED1 13
#define NUM_LEDS 300

Adafruit_NeoPixel strip = Adafruit_NeoPixel(300, PINLED1, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(30);
  strip.show(); // Initialize all pixels to 'off'

  //strip2.begin();
  //strip2.setBrightness(100);
  //strip2.show(); // Initialize all pixels to 'off'
  pinMode(BUTTON, INPUT_PULLUP); // internal pull-up resistor
  attachInterrupt (digitalPinToInterrupt (BUTTON), changeEffect, CHANGE); // pressed
  //attachInterrupt(0, changeEffect, CHANGE);

  strip.begin();
  strip.setBrightness(0);
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
    if (odebraneDane == "s0") strip.setBrightness(0)
    if (odebraneDane == "sufitoff") strip.setBrightness(0);



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

