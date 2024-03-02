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
    
    if (odebraneDane == "sufiton") { //Jeśli odebrano słowo "zielona"
      digitalWrite(zielona, HIGH); //To włączamy diodę zieloną
      delay(1000);
      digitalWrite(zielona, LOW); 
    }
    
    if (odebraneDane == "sufitoff") { //Jeśli odebrano słowo "czerwona"
      digitalWrite(czerwona, HIGH); //To włączamy diodę czerwoną
      delay(1000);
      digitalWrite(czerwona, LOW); 
    }

    if (odebraneDane == "tvon") { //Jeśli odebrano słowo "czerwona"
      digitalWrite(czerwona, HIGH); //To włączamy diodę czerwoną
      delay(1000);
      digitalWrite(czerwona, LOW); 
    }

    if (odebraneDane == "tvoff") { //Jeśli odebrano słowo "czerwona"
      digitalWrite(czerwona, HIGH); //To włączamy diodę czerwoną
      delay(1000);
      digitalWrite(czerwona, LOW); 
    }


  }
}

