#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PINLED1 13
#define PINLED2 12
#define BUTTON 2
#define NUM_LEDS 300

Adafruit_NeoPixel strip = Adafruit_NeoPixel(300, PINLED1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(144, PINLED2, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.setBrightness(30);
  strip.show(); // Initialize all pixels to 'off'

  //strip2.begin();
  //strip2.setBrightness(100);
  //strip2.show(); // Initialize all pixels to 'off'
  pinMode(BUTTON, INPUT_PULLUP); // internal pull-up resistor
  attachInterrupt (digitalPinToInterrupt (BUTTON), changeEffect, CHANGE); // pressed
  //attachInterrupt(0, changeEffect, CHANGE);
}
/* notatki new
dodac interrupta na sygnal IR
dodac interrupta programowego na break wheel gdy zmienna break_wheel = 1
dodac cos ala interrupta gdy cos z seriala przyjdzie ?


uart interrupt
https://www.reddit.com/r/arduino/comments/stj1jk/how_do_i_use_an_interrupt_for_user_serial_input/
*/


void loop() {
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //(strip.Color(127, 0, 0), 50); // Red
  //theaterChase(strip.Color(0, 0, 127), 50); // Blue
  //theaterChaseRainbow(20);
  
  // Some example procedures showing how to display to the pixels:
  /*
  colorWipe(strip.Color(255, 0, 0), 20); // Red
  colorWipe(strip.Color(0, 255, 0), 20); // Green
  colorWipe(strip.Color(0, 0, 255), 20); // Blue
  */
  //jasnosc1();
  //oldeffects_preset2();
  
  //rainbow(20);
  //rainbowCycle(20);
  jasnosc1();
  new_effects1();


  //rainbow(100);
  
//rainbow_dual(50);

  // new1
  //rainbow(1);
  //rainbowCycle(1);
  //wipe1();

  //rainbow(3);
  //rainbowCycle(3);

  //colorWipe(strip.Color(255, 0, 0), 20); // Red
  //colorWipe(strip.Color(0, 255, 0), 20); // Green
  //colorWipe(strip.Color(0, 0, 255), 20); // Blue
}


static bool jasnosc_on = 1;
volatile int jasnosc_prog = 5;
//orginalnie bylo static byte selectedEffect2 = 0;

void jasnosc1(){

if ((jasnosc_prog > 5) && (jasnosc_on == 1))  {
    jasnosc_prog = 0;
  }

  switch (jasnosc_prog) {

    case 0  : {
        strip.setBrightness(100);
        //strip.show();
        strip2.setBrightness(100);
        //strip2.show();
        break;
      }
    case 1  : {
        strip.setBrightness(50);
        //strip.show();
        strip2.setBrightness(100);
        //strip2.show();
        break;
      }
    case 2  : {
        strip.setBrightness(25);
        //strip.show();
        strip2.setBrightness(100);
        //strip2.show();
        break;
      }
      case 3  : {
        strip.setBrightness(15);
        //strip.show();
        strip2.setBrightness(15);
        //strip2.show();
        break;
      }
    case 4  : {
        strip.setBrightness(10);
        //strip.show();
        strip2.setBrightness(4);
        //strip2.show();
        break;
      }
    case 5  : {
        strip.setBrightness(0);
        //strip.show();
        strip2.setBrightness(0);
        //strip2.show();
        break;
      }
  }   
}

void changeEffect() {
  if (digitalRead (BUTTON) == LOW) {
    delay_200ms_from_microseconds();
    jasnosc_prog++;
    //if (jasnosc_prog > 2) jasnosc_prog = 0;
    //asm volatile ("  jmp 0");
    jasnosc1();
  }
}

/*
void changeEffect2() {
  if (digitalRead (BUTTON) == LOW) {
  //jasnosc_prog++;
    //if (jasnosc_prog > 2) jasnosc_prog = 0;
    //asm volatile ("  jmp 0");
  //jasnosc1();
  }
}
*/

void rainbow_dual(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel_dual((i+j) & 255));
      strip2.setPixelColor(i, Wheel_dual((i+j) & 255));
    }
    strip.show();
    strip2.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel_dual(byte WheelPos2) {
  WheelPos2 = 255 - WheelPos2;
  if(WheelPos2 < 85) {
    return strip2.Color(255 - WheelPos2 * 3, 0, WheelPos2 * 3);
  }
  if(WheelPos2 < 170) {
    WheelPos2 -= 85;
    return strip2.Color(0, WheelPos2 * 3, 255 - WheelPos2 * 3);
  }
  WheelPos2 -= 170;
  return strip2.Color(WheelPos2 * 3, 255 - WheelPos2 * 3, 0);
}

static bool new_effects1_on = 1;
volatile static int new_effects1_prog = 0;
//volatile static int new_effects1_prog = 2;

//rainbow buguje a rainbowcycle nie

void new_effects1(){

if (new_effects1_prog > 5){
      new_effects1_prog = 0;
    }
  if (new_effects1_on == 1){

  switch (new_effects1_prog) {

    case 0  : {
      //rainbow_dual(50);
      rainbowCycle(70);
        //strip2.show();
        break;
      }
    case 1  : {
        meteory_old1();
        break;
      }
    case 2  : {
        meteory_old2();
        break;
      }
    case 3  : {
        programy_old33();
        break;
      }
    case 4  : {
        break;
      }
      
    case 5  : {
      //rainbowCycle(15);
      //rainbow(15); //buguje sie
      
      //TwinkleRandom(50, 100, false);  //buguje sie
      // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        //meteorRain(255, 0x00, 100, 10, 64, true, 30);
        //meteorRain(255, 0x00, 185, 10, 64, true, 30);
        //meteorRain(255, 0x00, 255, 10, 64, true, 30);
        //meteorRain(255, 0x00, 255, 10, 64, true, 10);
        //meteorRain(255, 0x00, 255, 10, 32, true, 1);
        //meteorRain(255, 0x00, 255, 12, 10, true, 1);
      //meteorRain(125, 0, 255, 10, 10, true, 1);
        meteorRain(100, 0, 255, 10, 10, true, 1);
        //meteorRain(75, 0, 255, 10, 10, true, 1);
        //meteorRain(50, 0, 255, 10, 10, true, 1);
        
        //meteorRain(255, 0x00, 50, 10, 64, true, 30);
        
      /*
        RGBLoop(); //slabe
        rainbowCycle(15);

        // Twinkle - Color (red, green, blue), count, speed delay, only one twinkle (true/false)
      //Twinkle(0xff, 0x00, 0x00, 40, 100, false);
        // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        meteorRain(255, 0x00, 0, 10, 64, true, 30);
        //TwinkleRandom - twinkle count, speed delay, only one (true/false)
      TwinkleRandom(50, 100, false);
        meteorRain(255, 0x00, 255, 10, 64, true, 30);
        break;
        */
      }
      
    }
  }
}

/*
static int old_effects_on2 = 1;
static byte selectedEffect2 = 0;

*/
/*

void oldeffects_preset2() {

  if (selectedEffect2 > 1)  {
    selectedEffect2 = 0;
  }

  switch (selectedEffect2) {

    case 0  : {
        rainbow_dual(50);
        break;
      }

    case 1  : {
        rainbow_dual(55);
        break;
      }
  }
}
    */
   /*
      case 2  : {
        // FadeInOut - Color (red, green. blue)
        //FadeInOut(0xff, 0x00, 0x00); // red
        //FadeInOut(0xff, 0xff, 0xff); // white
        //FadeInOut(0x00, 0x00, 0xff); // blue
        rainbow_dual(50);
        break;
      }
      case 3  : {
        // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        //meteorRain(0xff, 0, 0xff, 7, 64, true, 5);
        break;
      }
      case 4  : {
        // FadeInOut - Color (red, green. blue)
        //FadeInOut(0xff, 0x00, 0x00); // red
        //FadeInOut(0xff, 0xff, 0xff); // white
        //FadeInOut(0x00, 0x00, 0xff); // blue
        rainbow_dual(50);
        break;
      }
      case 5  : {
        fadeInRainbow(20);
        rainbowCycleWithSparkle(1, 20);
        fadeOutRainbow(30);
        fadeInRainbow(20);
        rainbowCycle(20);
        fadeOutRainbow(35);
        break;
      }
      case 6  : {
        break;
      }
      */

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

/*
void Sparkle2() {
  int k2;
  // for random miedzy 10 a 1000
  for (k2 = 0; k2 < random (100, 200); k2++) {
    // r g b oraz delay miedzy sparklami
    Sparkle(120, 0x00, 120, 30);
  }
}

*/


//funkcje neo2

// ***************************************
// ** FastLed/NeoPixel Common Functions **
// ***************************************

// Apply LED color changes
void showStrip() {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.show();
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  FastLED.show();
#endif
}


// Set a LED color (not yet visible)
void setPixel(int Pixel, byte red, byte green, byte blue) {
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  strip.setPixelColor(Pixel, strip.Color(red, green, blue));
  strip2.setPixelColor(Pixel, strip2.Color(red, green, blue));
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
#endif
}

// Set all LEDs to a given color and apply it (visible)
void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}



void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    setPixel(i, red, green, blue);
    showStrip();
    delay(SpeedDelay);
  }
}



// *************************
// ** LEDEffect Functions **
// *************************

void Fire2(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS];
  int cooldown;
 
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
   
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
 
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
   
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor2(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}

void setPixelHeatColor2 (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}


void RGBLoop(){
  for(int j = 0; j < 3; j++ ) {
    // Fade IN
    for(int k = 0; k < 256; k++) {
      switch(j) {
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k--) {
      switch(j) {
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
  }
}

void FadeInOut(byte red, byte green, byte blue){
  float r, g, b;
     
  for(int k = 0; k < 256; k=k+1) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
  }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
  }
}

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause){
  for(int j = 0; j < StrobeCount; j++) {
    setAll(red,green,blue);
    showStrip();
    delay(FlashDelay);
    setAll(0,0,0);
    showStrip();
    delay(FlashDelay);
  }
 
 delay(EndPause);
}

void HalloweenEyes(byte red, byte green, byte blue,
                   int EyeWidth, int EyeSpace,
                   boolean Fade, int Steps, int FadeDelay,
                   int EndPause){
  randomSeed(analogRead(0));
 
  int i;
  int StartPoint  = random( 0, NUM_LEDS - (2*EyeWidth) - EyeSpace );
  int Start2ndEye = StartPoint + EyeWidth + EyeSpace;
 
  for(i = 0; i < EyeWidth; i++) {
    setPixel(StartPoint + i, red, green, blue);
    setPixel(Start2ndEye + i, red, green, blue);
  }
 
  showStrip();
 
  if(Fade==true) {
    float r, g, b;
 
    for(int j = Steps; j >= 0; j--) {
      r = j*(red/Steps);
      g = j*(green/Steps);
      b = j*(blue/Steps);
     
      for(i = 0; i < EyeWidth; i++) {
        setPixel(StartPoint + i, r, g, b);
        setPixel(Start2ndEye + i, r, g, b);
      }
     
      showStrip();
      delay(FadeDelay);
    }
  }
 
  setAll(0,0,0); // Set all black
 
  delay(EndPause);
}

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
 
  delay(ReturnDelay);
}

void NewKITT(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
  CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
}

// used by NewKITT
void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i =((NUM_LEDS-EyeSize)/2); i>=0; i--) {
    setAll(0,0,0);
   
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
   
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue);
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
   
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}



// used by NewKITT
void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i<=((NUM_LEDS-EyeSize)/2); i++) {
    setAll(0,0,0);
   
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
   
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue);
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
   
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

// used by NewKITT
void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

// used by NewKITT
void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
 
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),red,green,blue);
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) {
       setAll(0,0,0);
     }
   }
 
  delay(SpeedDelay);
}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
 
  for (int i=0; i<Count; i++) {
     setPixel(random(NUM_LEDS),random(0,255),random(0,255),random(0,255));
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) {
       setAll(0,0,0);
     }
   }
 
  delay(SpeedDelay);
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel,0,0,0);
}

void SnowSparkle(byte red, byte green, byte blue, int SparkleDelay, int SpeedDelay) {
  setAll(red,green,blue);
 
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,0xff,0xff,0xff);
  showStrip();
  delay(SparkleDelay);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position=0;
 
  for(int i=0; i<NUM_LEDS*2; i++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
     
      showStrip();
      delay(WaveDelay);
  }
}

//funkcje NEO i adafruit


void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS];
  int cooldown;
 
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
   
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
 
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
   
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}

void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}

void BouncingColoredBalls(int BallCount, byte colors[][3], boolean continuous) {
  float Gravity = -9.81;
  int StartHeight = 1;
 
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
  boolean ballBouncing[BallCount];
  boolean ballsStillBouncing = true;
 
  for (int i = 0 ; i < BallCount ; i++) {  
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2);
    ballBouncing[i]=true;
  }

  while (ballsStillBouncing) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
 
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
 
        if ( ImpactVelocity[i] < 0.01 ) {
          if (continuous) {
            ImpactVelocity[i] = ImpactVelocityStart;
          } else {
            ballBouncing[i]=false;
          }
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }

    ballsStillBouncing = false; // assume no balls bouncing
    for (int i = 0 ; i < BallCount ; i++) {
      setPixel(Position[i],colors[i][0],colors[i][1],colors[i][2]);
      if ( ballBouncing[i] ) {
        ballsStillBouncing = true;
      }
    }
   
    showStrip();
    setAll(0,0,0);
  }
}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  setAll(0,0,0);
 
  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
   
   
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
   
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      }
    }
   
    showStrip();
    delay(SpeedDelay);
  }
}

// used by meteorrain
void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
   
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
   
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}

///// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// nowe z neta
// https://www.tweaking4all.com/forum/arduino/led-effects-fade-out-on-rainbow-cycle/

//

//fadeInRainbow
/* old ver with error
void fadeInRainbow(int SpeedDelay) {

  byte *c;
  uint16_t i, j;
  for (j = 0; j < 256; j = j + 1) {
    for (i = 0; i < NUM_LEDS; i++) {
      c = Wheel_uint32((i * 256 / NUM_LEDS) & 255);
      setPixel(i, *c * (j / 256.0), *(c + 1) * (j / 256.0), *(c + 2) * (j / 256.0));
    }

    showStrip();
    delay(SpeedDelay);
  }
}
*/

void fadeInRainbow(int SpeedDelay) {
  uint32_t color;
  uint8_t r, g, b;
  for (uint16_t j = 0; j < 256; j++) {
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
      color = Wheel((i * 256 / NUM_LEDS) & 255);
      // Extract individual color components
      r = (color >> 16) & 0xFF;
      g = (color >> 8) & 0xFF;
      b = color & 0xFF;
      // Modify the color components based on fade value (j)
      r = (r * j) / 256;
      g = (g * j) / 256;
      b = (b * j) / 256;
      // Set the pixel with the modified color
      setPixel(i, r, g, b);
    }
    showStrip();
    delay(SpeedDelay);
  }
}

//fadeOutRainbow
void fadeOutRainbow(int SpeedDelay) {

  // 53 times reduce the color brightness by 10%, reaching close to zero (black)
  for (int j = 1; j < 53; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      fadeToBlack(i, 26); // 26 / 256 = 10% brightness reduction
    }

    showStrip();
    delay(SpeedDelay);
  }
}


//colorWipeReversed
void colorWipeReversed(byte red, byte green, byte blue, int SpeedDelay) {
  for (uint16_t i = NUM_LEDS; i > 0; i--) {
    setPixel(i, red, green, blue);
    showStrip();
    delay(SpeedDelay);
  }
}

//RainbowCycleWithSparkle
/* old error ver
void rainbowCycleWithSparkle(int SparkleDelay, int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < NUM_LEDS; i++) {
      c = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c + 1), *(c + 2));
    }

    showStrip();
    delay(SpeedDelay);
    int Pixel = random(NUM_LEDS);
    setPixel(Pixel, 0xff, 0xff, 0xff);
    showStrip();
    delay(SparkleDelay);
  }
}
*/

void rainbowCycleWithSparkle(int SparkleDelay, int SpeedDelay) {
  uint32_t color;
  uint8_t r, g, b;
  for (uint16_t j = 0; j < 256; j++) {
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
      color = Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      // Extract individual color components
      r = (color >> 16) & 0xFF;
      g = (color >> 8) & 0xFF;
      b = color & 0xFF;
      // Set the pixel with the extracted color
      setPixel(i, r, g, b);
    }

    showStrip();
    delay(SpeedDelay);
    int Pixel = random(NUM_LEDS);
    setPixel(Pixel, 0xff, 0xff, 0xff); // Set sparkle color (white)
    showStrip();
    delay(SparkleDelay);
  }
}

//meteorRainTransition
void meteorRainTransition(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {
  setAll(0, 0, 0);

  // old:
  // for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {

  // new:
  for (int i = 0; i < NUM_LEDS; i++) {

    // fade brightness all LEDs one step
    for (int j = 0; j < NUM_LEDS; j++) {
      if ( (!meteorRandomDecay) || (random(10) > 5) ) {
        fadeToBlack(j, meteorTrailDecay );
      }
    }

    // draw meteor
    for (int j = 0; j < meteorSize; j++) {
      if ( ( i - j < NUM_LEDS) && (i - j >= 0) ) {
        setPixel(i - j, red, green, blue);
      }
    }

    showStrip();
    delay(SpeedDelay);
  }
}

  ///funkcje gotowe sekwencje

  //


void programy_old1(){
  
}

void programy_old2(){
  
}

void programy_old3(){
  
}

void programy_old4(){
  
}

void programy_old5(){
  
}

void programy_old6(){
  
}

void programy_old7(){
  
}

void programy_old8(){
  
}

void programy_old9(){
  
}

void programy_old10(){
  
}

void programy_old11(){
  
}

void programy_old12(){
  
}

void programy_old13(){
  
}

void programy_old14(){
  
}

void programy_old32(){
        // ladne po kolei
        // CylonBounce - Color (red, green, blue), eye size, speed delay, end pause
        CylonBounce(0xff, 0x00, 50, 7, 40, 30);
        CylonBounce(0, 0, 255, 7, 40, 40);

        //              NewKITT - Color (red, green, blue), eye size, speed delay, end pause
        NewKITT(0xff, 0x00, 0x00, 8, 40, 50);
        // Twinkle - Color (red, green, blue), count, speed delay, only one twinkle (true/false)
        Twinkle(0xff, 0x00, 0x00, 40, 300, false);
        // TwinkleRandom - twinkle count, speed delay, only one (true/false)
        TwinkleRandom(50, 100, false);
        // Sparkle - Color (red, green, blue), speed delay
        Sparkle(0xff, 0xff, 0xff, 0);
        Sparkle(255, 0, 0, 0);
        Sparkle(0, 255, 0, 0);
        Sparkle(0, 0, 255, 0);
        Sparkle(255, 0, 255, 0);
        // SnowSparkle - Color (red, green, blue), sparkle delay, speed delay
        //SnowSparkle(0x10, 0x10, 0x10, 200, random(100,1000));
        // Running Lights - Color (red, green, blue), wave dealy
        //RunningLights(0xff,0x00,0x00, 30);  // red
        //RunningLights(0xff,0xff,0xff, 50);  // white
        //RunningLights(255,0x00,255, 30);  // pink
        //RunningLights(125,0x00,125, 30);  // pink low
        //RunningLights(150,0x00,255, 30);  // violet
        //RunningLights(0x00,0x00,0xff, 30);  // blue
        // colorWipe - Color (red, green, blue), speed delay
        colorWipe(0xff, 30);
        //colorWipe(0x00,0x00,0x00, 50);
        // rainbowCycle - speed delay
        rainbowCycle(10);
        // theatherChase - Color (red, green, blue), speed delay
      //theaterChase(0xff, 0, 0, 250);
        // theaterChaseRainbow - Speed delay
        //theaterChaseRainbow(50);
        // Fire - Cooling rate, Sparking rate, speed delay
        int k3;
        for (k3 = 0; k3 < random (500, 3000); k3++) {
          Fire(55, 120, 15);
        }
        // simple bouncingBalls not included, since BouncingColoredBalls can perform this as well as shown below
        // BouncingColoredBalls - Number of balls, color (red, green, blue) array, continuous
        // CAUTION: If set to continuous then this effect will never stop!!!

        // mimic BouncingBalls
        byte onecolor[1][3] = { {0xff, 0x00, 0x00} };
        BouncingColoredBalls(1, onecolor, false);
        // multiple colored balls
        byte colors[3][3] = { {0xff, 0x00, 0x00},
          {0xff, 0xff, 0xff},
          {0x00, 0x00, 0xff}
        };
        BouncingColoredBalls(3, colors, false);

        // meteorRain BLUE - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        meteorRain(0x00, 0x00, 0xff, 10, 64, true, 30);

        fadeInRainbow(5);
        fadeOutRainbow(20);
        fadeInRainbow(5);
        fadeOutRainbow(20);

        rainbowCycleWithSparkle(50, 20);

        //colorWipe(0x00, 0x00, 0xff, 30);
        colorWipeReversed(120, 0x00, 0x00, 15);
        int k2;
        for (k2 = 0; k2 < random (500, 3000); k2++) {
          Sparkle(0xff, 0x00, 0xff, 0);
        }
        meteorRain(0x00, 0x00, 0xff, 10, 64, true, 10);

}

void programy_old33(){
        // multiprog2 tlo
      //RGBLoop();  //nudne
        //fadeInRainbow(15);    //nie dziala
        //fadeOutRainbow(70);   //nie dziala
        //fadeInRainbow(25);    //nie dziala
        rainbowCycle(15);

        
        //rainnow cycle with sparkle sparkle delay, speed delay
        //rainbowCycleWithSparkle(500, 10); //nie dziala
        
        // Twinkle - Color (red, green, blue), count, speed delay, only one twinkle (true/false)
      //Twinkle(0xff, 0x00, 0x00, 40, 100, false);
        // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        meteorRain(255, 0x00, 0, 10, 64, true, 30);
        
        //TwinkleRandom - twinkle count, speed delay, only one (true/false)
      //TwinkleRandom(50, 100, false);
        meteorRain(255, 0x00, 255, 10, 64, true, 30);
      //TwinkleRandom(50, 100, false);
        meteorRain(0x00, 0x00, 255, 10, 64, true, 30);
        /*
        // Fire - Cooling rate, Sparking rate, speed delay  //nie dziala
        int k3;
        for (k3 = 0; k3 < random (500, 3000); k3++) {
          Fire(55, 120, 15);
        }
        */
}

void meteory_old1(){
  // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        meteorRain(255, 125, 0, 10, 20, true, 30);
        
        meteorRain(255, 0, 0, 8, 60, true, 30);
        meteorRain(255, 0, 255, 10, 64, true, 30);
        
        meteorRain(255, 0, 120, 7, 100, true, 30);
        meteorRain(255, 0, 20, 10, 64, true, 30);
        meteorRain(150, 0, 255, 10, 150, true, 30);
        meteorRain(50, 0, 255, 10, 34, true, 30);
        
        meteorRain(0, 0, 255, 10, 64, true, 30);
        meteorRain(0, 255, 0, 10, 64, true, 30);
        meteorRain(255, 255, 0, 10, 64, true, 30);
        
        meteorRain(255, 75, 0, 10, 50, true, 30);
  }

void meteory_old2(){
        //METEORY old
        // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        int speed_meteory1 = 60;
        meteorRain(255, 125, 0, 10, 20, true, speed_meteory1);
        
        meteorRain(255, 0, 0, 8, 60, true, speed_meteory1);
        meteorRain(255, 0, 255, 10, 64, true, speed_meteory1);
        
        meteorRain(255, 0, 120, 7, 100, true, speed_meteory1);
        meteorRain(255, 0, 20, 10, 64, true, speed_meteory1);
        meteorRain(150, 0, 255, 10, 150, true, speed_meteory1);
        meteorRain(50, 0, 255, 10, 34, true, speed_meteory1);
        
        meteorRain(0, 0, 255, 10, 64, true, speed_meteory1);
        meteorRain(0, 255, 0, 10, 64, true, speed_meteory1);
        meteorRain(255, 255, 0, 10, 64, true, speed_meteory1);
        
        meteorRain(255, 75, 0, 10, 50, true, speed_meteory1);
}
  
/*
static byte selectedEffect = 35;
static int old_effects_on = 1;

void oldeffects_preset(){

  if ((selectedEffect > 50) && (old_effects_on == 1))  {
    selectedEffect = 0;
  }

  switch (selectedEffect) {

    case 50  : {
       rainbow_dual(50);
      }

    case 0  : {
        // RGBLoop - no parameters
      //RGBLoop();
        //RGBLoop2(); brakuje
      }

    case 1  : {
        // FadeInOut - Color (red, green. blue)
        FadeInOut(0xff, 0x00, 0x00); // red
        FadeInOut(0xff, 0xff, 0xff); // white
        FadeInOut(0x00, 0x00, 0xff); // blue
        break;
      }


    case 2 : {
        fadeInRainbow(20);
        rainbowCycleWithSparkle(1, 20);
        fadeOutRainbow(30);
        fadeInRainbow(20);
        rainbowCycle(20);
        fadeOutRainbow(35);

        break;
      }
    
        case 2  : {
                    // Strobe - Color (red, green, blue), number of flashes, flash speed, end pause
                    Strobe(0xff, 0xff, 0xff, 10, 50, 1000);
                    break;
                  }
    
    case 3  : {
        // HalloweenEyes - Color (red, green, blue), Size of eye, space between eyes, fade (true/false), steps, fade delay, end pause
        HalloweenEyes(0xff, 0x00, 0x00,
                      1, 4,
                      true, random(5, 50), random(50, 150),
                      random(1000, 1000));
        HalloweenEyes(0xff, 0x00, 0x00,
                      1, 4,
                      true, random(5, 50), random(50, 150),
                      random(1000, 1000));
        break;
      }

    case 4  : {
        // CylonBounce - Color (red, green, blue), eye size, speed delay, end pause
        CylonBounce(0xff, 0x00, 0x00, 7, 20, 50);
        break;
      }

    case 5  : {
        // NewKITT - Color (red, green, blue), eye size, speed delay, end pause
        NewKITT(0xff, 0x00, 0x00, 8, 10, 50);
        break;
      }

    case 6  : {
        // Twinkle - Color (red, green, blue), count, speed delay, only one twinkle (true/false)
        Twinkle(0xff, 0x00, 0x00, 100, 100, false);
        break;
      }

    case 7  : {
        // TwinkleRandom - twinkle count, speed delay, only one (true/false)
        TwinkleRandom(1500, 250, false);
        break;
      }

    case 8  : {
        // Sparkle - Color (red, green, blue), speed delay
        //   Sparkle(0xff, 0xff, 0xff, 0);
        Sparkle(255, 0, 255, 50);
           //Sparkle(0xff, 0xff, 0xff, 300);
           //Sparkle(255, 0, 0, 250);
           //Sparkle(0, 255, 0, 100);
           //Sparkle(0, 0, 255, 150);
           //Sparkle(255, 0, 255, 200);
        
        break;
      }

    case 9  : {
        // SnowSparkle - Color (red, green, blue), sparkle delay, speed delay
        SnowSparkle(0x10, 0x10, 0x10, 20, random(100, 1000));
        break;
      }

    case 10 : {
        // Running Lights - Color (red, green, blue), wave dealy
        //RunningLights(0xff,0x00,0x00, 30);  // red
        //RunningLights(0xff,0xff,0xff, 50);  // white
        RunningLights(255, 0x00, 255, 30); // pink
        //RunningLights(125,0x00,125, 30);  // pink low
        //RunningLights(150,0x00,255, 30);  // violet
        //RunningLights(0x00,0x00,0xff, 30);  // blue
        break;
      }

    case 11 : {
        // colorWipe - Color (red, green, blue), speed delay
      //colorWipe(0x00, 0x00, 0xff, 50);
      //colorWipe(0x00, 0x00, 0x00, 50);
        break;
      }

    case 12 : {
        // rainbowCycle - speed delay
        rainbowCycle(20);
        break;
      }

    case 13 : {
        // theatherChase - Color (red, green, blue), speed delay
        //theaterChase(0xff, 0, 0, 50);
        break;
      }

    case 14 : {
        // theaterChaseRainbow - Speed delay
        theaterChaseRainbow(50);
        break;
      }

    case 15 : {
        // Fire - Cooling rate, Sparking rate, speed delay
        Fire(55, 120, 15);
        break;
      }


    // simple bouncingBalls not included, since BouncingColoredBalls can perform this as well as shown below
    // BouncingColoredBalls - Number of balls, color (red, green, blue) array, continuous
    // CAUTION: If set to continuous then this effect will never stop!!!

    case 16 : {
        // mimic BouncingBalls
        byte onecolor[1][3] = { {0xff, 0x00, 0x00} };
        BouncingColoredBalls(1, onecolor, false);
        break;
      }

    case 17 : {
        // multiple colored balls
        byte colors[3][3] = { {0xff, 0x00, 0x00},
          {0xff, 0xff, 0xff},
          {0x00, 0x00, 0xff}
        };
        BouncingColoredBalls(3, colors, false);
        break;
      }

    case 18 : {
        // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        meteorRain(0xff, 0, 0xff, 7, 64, true, 5);
        break;
      }

    case 19 : {
        // Fire2 - Cooling rate, Sparking rate, speed delay
        Fire2(55, 200, 1000);
        break;
      }
    // NOWE z neta

    case 20 : {
        fadeInRainbow(5);
        break;
      }
    case 21 : {
        fadeInRainbow(5);
        fadeOutRainbow(20);
        break;
      }
    case 22 : {
        rainbowCycleWithSparkle(50, 20);
        break;
      }
    case 23 : {
        {
          colorWipeReversed(0xff, 0xff, 0xff, 10);
          // colorWipeReversed(0x00,0x00,0x00, 20);
        }
        int k;
        for (k = 0; k < random (1000, 5000); k++) {
          Sparkle(0xff, 0xff, 0xff, 0);
        }
        break;
      }
    //moje
    case 24 : {
        //color wipe sparke potem meteor white slow
        {
          colorWipeReversed(0xff, 0xff, 0xff, 30);
          // colorWipeReversed(0x00,0x00,0x00, 20);
        }
        int k;
        for (k = 0; k < random (300, 3000); k++) {
          Sparkle(0xff, 0xff, 0xff, 0);
        }
        meteorRain(0xff, 0xff, 0xff, 10, 64, true, 30);
        break;
      }
    case 25 : {
        //color wipe sparke potem meteor white fast
        {
          colorWipeReversed(0xff, 0xff, 0xff, 10);
          // colorWipeReversed(0x00,0x00,0x00, 20);
        }
        int k;
        for (k = 0; k < random (300, 3000); k++) {
          Sparkle(0xff, 0xff, 0xff, 0);
        }
        meteorRain(0xff, 0xff, 0xff, 10, 64, true, 10);
        break;
      }
    case 26 : {
        //color wipe sparke potem meteor blue slow
        {
          colorWipeReversed(0x00, 0x00, 0xff, 30);
          // colorWipeReversed(0x00,0x00,0x00, 20);
        }
        int k;
        for (k = 0; k < random (300, 3000); k++) {
          Sparkle(0xff, 0xff, 0xff, 0);
        }
        meteorRain(0x00, 0x00, 0xff, 10, 64, true, 30);
        break;
      }
    case 27 : {
        //color wipe sparke potem meteor blue fast
        {
          colorWipeReversed(0x00, 0x00, 0xff, 10);
          // colorWipeReversed(0x00,0x00,0x00, 20);
        }
        int k;
        for (k = 0; k < random (300, 3000); k++) {
          Sparkle(0xff, 0xff, 0xff, 0);
        }
        meteorRain(0x00, 0x00, 0xff, 10, 64, true, 10);
        break;
      }
    case 28 : {
        //meteory dwie strony
        colorWipeReversed(120, 0x00, 5, 30);
        colorWipeReversed(0, 0, 0, 30);
        // Sparkle2();
        // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        meteorRain(0x00, 0x00, 0xff, 10, 64, true, 30);
        break;
      }
    case 29 : {
        //color wipe sparke potem meteor kolory slow pink
        colorWipeReversed(120, 0x00, 5, 25);
        // colorWipeReversed(0x00,0x00,0x00, 20);
      //colorWipe(5, 0x00, 120, 25);
        colorWipeReversed(0, 0, 0, 25);
        //  Sparkle2();
        // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        meteorRain(0x00, 0x00, 0xff, 10, 64, true, 20);
        break;
      }
    case 30 : {
        //color wipe sparke potem meteor kolory slow sparkle pink
        colorWipeReversed(120, 0x00, 5, 25);
        // colorWipeReversed(0x00,0x00,0x00, 20);
      //colorWipe(5, 0x00, 120, 25);
        colorWipeReversed(0, 0, 0, 25);
        Sparkle2();
        // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        meteorRain(0x00, 0x00, 0xff, 10, 64, true, 20);
        break;
      }
    case 31 : {
        // meteorRain BLUE - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        meteorRain(0x00, 0x00, 0xff, 10, 64, true, 30);
        break;
      }
    case 32 : {
        // ladne po kolei
        // CylonBounce - Color (red, green, blue), eye size, speed delay, end pause
        CylonBounce(0xff, 0x00, 50, 7, 40, 30);
        CylonBounce(0, 0, 255, 7, 40, 40);

        //              NewKITT - Color (red, green, blue), eye size, speed delay, end pause
        NewKITT(0xff, 0x00, 0x00, 8, 40, 50);
        // Twinkle - Color (red, green, blue), count, speed delay, only one twinkle (true/false)
        Twinkle(0xff, 0x00, 0x00, 40, 300, false);
        // TwinkleRandom - twinkle count, speed delay, only one (true/false)
        TwinkleRandom(50, 100, false);
        // Sparkle - Color (red, green, blue), speed delay
        Sparkle(0xff, 0xff, 0xff, 0);
        Sparkle(255, 0, 0, 0);
        Sparkle(0, 255, 0, 0);
        Sparkle(0, 0, 255, 0);
        Sparkle(255, 0, 255, 0);
        // SnowSparkle - Color (red, green, blue), sparkle delay, speed delay
        //SnowSparkle(0x10, 0x10, 0x10, 200, random(100,1000));
        // Running Lights - Color (red, green, blue), wave dealy
        //RunningLights(0xff,0x00,0x00, 30);  // red
        //RunningLights(0xff,0xff,0xff, 50);  // white
        //RunningLights(255,0x00,255, 30);  // pink
        //RunningLights(125,0x00,125, 30);  // pink low
        //RunningLights(150,0x00,255, 30);  // violet
        //RunningLights(0x00,0x00,0xff, 30);  // blue
        // colorWipe - Color (red, green, blue), speed delay
        colorWipe(0xff, 30);
        //colorWipe(0x00,0x00,0x00, 50);
        // rainbowCycle - speed delay
        rainbowCycle(10);
        // theatherChase - Color (red, green, blue), speed delay
      //theaterChase(0xff, 0, 0, 250);
        // theaterChaseRainbow - Speed delay
        //theaterChaseRainbow(50);
        // Fire - Cooling rate, Sparking rate, speed delay
        int k3;
        for (k3 = 0; k3 < random (500, 3000); k3++) {
          Fire(55, 120, 15);
        }
        // simple bouncingBalls not included, since BouncingColoredBalls can perform this as well as shown below
        // BouncingColoredBalls - Number of balls, color (red, green, blue) array, continuous
        // CAUTION: If set to continuous then this effect will never stop!!!

        // mimic BouncingBalls
        byte onecolor[1][3] = { {0xff, 0x00, 0x00} };
        BouncingColoredBalls(1, onecolor, false);
        // multiple colored balls
        byte colors[3][3] = { {0xff, 0x00, 0x00},
          {0xff, 0xff, 0xff},
          {0x00, 0x00, 0xff}
        };
        BouncingColoredBalls(3, colors, false);

        // meteorRain BLUE - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        meteorRain(0x00, 0x00, 0xff, 10, 64, true, 30);

        fadeInRainbow(5);
        fadeOutRainbow(20);
        fadeInRainbow(5);
        fadeOutRainbow(20);

        rainbowCycleWithSparkle(50, 20);

        //colorWipe(0x00, 0x00, 0xff, 30);
        colorWipeReversed(120, 0x00, 0x00, 15);
        int k2;
        for (k2 = 0; k2 < random (500, 3000); k2++) {
          Sparkle(0xff, 0x00, 0xff, 0);
        }
        meteorRain(0x00, 0x00, 0xff, 10, 64, true, 10);
        break;

      }
    case 33 : {
        // multiprog2 tlo
        RGBLoop();
        fadeInRainbow(15);
        fadeOutRainbow(70);
        fadeInRainbow(25);
        rainbowCycle(15);
        //rainnow cycle with sparkle sparkle delay, speed delay
        rainbowCycleWithSparkle(500, 10);
        
        // Twinkle - Color (red, green, blue), count, speed delay, only one twinkle (true/false)
      //Twinkle(0xff, 0x00, 0x00, 40, 100, false);
        // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        meteorRain(255, 0x00, 0, 10, 64, true, 30);
        //TwinkleRandom - twinkle count, speed delay, only one (true/false)
      //TwinkleRandom(50, 100, false);
        meteorRain(255, 0x00, 255, 10, 64, true, 30);
      //TwinkleRandom(50, 100, false);
        meteorRain(0x00, 0x00, 255, 10, 64, true, 30);

        // Fire - Cooling rate, Sparking rate, speed delay
        int k3;
        for (k3 = 0; k3 < random (500, 3000); k3++) {
          Fire(55, 120, 15);
        }

        meteorRain(0x00, 0x00, 0xff, 10, 64, true, 30);
        break;
      }

      case 34 : {
        //METEORY NEW
        // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        meteorRain(255, 125, 0, 10, 20, true, 30);
        
        meteorRain(255, 0, 0, 8, 60, true, 30);
        meteorRain(255, 0, 255, 10, 64, true, 30);
        
        meteorRain(255, 0, 120, 7, 100, true, 30);
        meteorRain(255, 0, 20, 10, 64, true, 30);
        meteorRain(150, 0, 255, 10, 150, true, 30);
        meteorRain(50, 0, 255, 10, 34, true, 30);
        
        meteorRain(0, 0, 255, 10, 64, true, 30);
        meteorRain(0, 255, 0, 10, 64, true, 30);
        meteorRain(255, 255, 0, 10, 64, true, 30);
        
        meteorRain(255, 75, 0, 10, 50, true, 30);
      }
      case 35 : {
        //METEORY NEW
        // meteorRain - Color (red, green, blue), meteor size, trail decay, random trail decay (true/false), speed delay
        int speed_meteory1 = 60;
        meteorRain(255, 125, 0, 10, 20, true, speed_meteory1);
        
        meteorRain(255, 0, 0, 8, 60, true, speed_meteory1);
        meteorRain(255, 0, 255, 10, 64, true, speed_meteory1);
        
        meteorRain(255, 0, 120, 7, 100, true, speed_meteory1);
        meteorRain(255, 0, 20, 10, 64, true, speed_meteory1);
        meteorRain(150, 0, 255, 10, 150, true, speed_meteory1);
        meteorRain(50, 0, 255, 10, 34, true, speed_meteory1);
        
        meteorRain(0, 0, 255, 10, 64, true, speed_meteory1);
        meteorRain(0, 255, 0, 10, 64, true, speed_meteory1);
        meteorRain(255, 255, 0, 10, 64, true, speed_meteory1);
        
        meteorRain(255, 75, 0, 10, 50, true, speed_meteory1);
      }
  }
}

*/


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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

// Fill the dots one after the other with a color
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

void delay_50ms_from_microseconds(){
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
}

void delay_100ms_from_microseconds(){
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
}

void delay_200ms_from_microseconds(){
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
  delayMicroseconds(10000);
}
