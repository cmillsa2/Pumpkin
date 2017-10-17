#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 4
#define LEDS 10

#define BLUE      0x0000FF
#define ROYALBLUE    0x4169E1
#define DARKBLUE    0x00008B
#define DARKGREEN    0x006400
#define GREEN      0x008000
#define OLIVEDRAB    0x6B8E23
#define BEIGE      0xF5F5DC
#define LINEN      0xFAF0E6
#define SPRINGGREEN    0x00FF7F
#define FORESTGREEN    0x228B22
#define DARKOLIVEGREEN    0x556B2F
#define GREENYELLOW    0xADFF2F
#define LAWNGREEN    0x7CFC00
#define LIGHTYELLOW    0xFFFFE0
#define YELLOW      0xFFFF00
#define LEMONCHIFFON    0xFFFACD
#define MOCCASIN    0xFFE4B5
#define LIGHTYELLOW    0xFFFFE0
#define PALEGOLDENROD    0xEEE8AA
#define DARKORANGE    0xFF8C00
#define ORANGE      0xFFA500
#define BLACK      0x000000

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int tears = 200; // Delay for tears 
int wait = 5000; //time between burts of tears
int flicker = 25;
int bombtick = 300;

int ledState1 = LOW;
unsigned long previousMillis1 = 0;
long OnTime1 = 2000;
long OffTime1 = 100;

int ledState2 = LOW;
unsigned long previousMillis2 = 0;
long OnTime2 = 500;
long OffTime2 = 6000;

long BombDelay = 0;
unsigned long PrevBomb = 0;





void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void staticlight1(){
    strip.setPixelColor(0, ORANGE );  //
    strip.setPixelColor(1, YELLOW );  //
    strip.setPixelColor(2, ORANGE );  //
    strip.setPixelColor(3, YELLOW );  //
    strip.setPixelColor(4, ORANGE );  //
    strip.show();                     //
}

void staticlight2(){
    strip.setPixelColor(5, ORANGE );  //
    strip.setPixelColor(6, YELLOW );  //
    strip.setPixelColor(7, ORANGE );  //
    strip.setPixelColor(8, YELLOW );  //
    strip.setPixelColor(9, ORANGE );  //
    strip.show();
}


void blue(){
    strip.setPixelColor(0, ROYALBLUE );  //
    strip.setPixelColor(1, ROYALBLUE );  //
    strip.setPixelColor(2, ROYALBLUE );  //
    strip.setPixelColor(3, ROYALBLUE );  //
    strip.setPixelColor(4, ROYALBLUE );  //
    strip.show();                        //
}

void shots(){
  for (int b=0; b <= 10; b++){
    blue();
    staticlight1();
  }
}


void bomb(){
  strip.setPixelColor(5, BLACK);
  strip.setPixelColor(6, BLACK);
  strip.setPixelColor(7, BLACK);
  strip.setPixelColor(8, BLACK);
  strip.setPixelColor(9, BLACK);
  for (int z=5; z<=LEDS; z++){
    strip.setPixelColor(z, GREEN);
    strip.show();
    delay(bombtick);
  }
}

void bob(){
  strip.setPixelColor(5, BLACK); 
  strip.setPixelColor(6, BLACK);
  strip.setPixelColor(7, BLACK);
  strip.setPixelColor(8, BLACK);
  strip.setPixelColor(9, BLACK);
  
  unsigned long bobclock = millis();
  unsigned long clockdiff = 100;
  
  if (bobclock - BombDelay >= PrevBomb){
    strip.setPixelColor(5, GREEN);
    strip.show();
    PrevBomb = bobclock;
    if (bobclock - BombDelay >= PrevBomb){
      strip.setPixelColor(6, GREEN);
      strip.show();
      PrevBomb = bobclock;
      if (bobclock - BombDelay >= PrevBomb){
        strip.setPixelColor(7, GREEN);
        strip.show();
        PrevBomb = bobclock;
        if (bobclock - BombDelay >= PrevBomb){
          strip.setPixelColor(8, GREEN);
          strip.show();
          PrevBomb = bobclock;
          if (bobclock - BombDelay >= PrevBomb){
            strip.setPixelColor(9, GREEN);
            strip.show();
            PrevBomb = bobclock;
          }
        }
      }
    }  
  }
}





void loop() 
{
  unsigned long currentMillis = millis();
  if((ledState1 == HIGH) && (currentMillis - previousMillis1 >= OnTime1)){
    ledState1 = LOW;
    previousMillis1 = currentMillis;
    blue();
    
  }
  else if ((ledState1 == LOW) && (currentMillis - previousMillis1 >= OffTime1)){
    ledState1 = HIGH;
    previousMillis1 = currentMillis;
    staticlight1();
    
  }
  if ((ledState2 == HIGH) && (currentMillis - previousMillis2 >= OnTime2)){
    ledState2 = LOW;
    previousMillis2 = currentMillis;
    staticlight2();
  }
  else if ((ledState2 == LOW) && (currentMillis - previousMillis2 >= OffTime2)){
    ledState2 = HIGH;
    previousMillis2 = currentMillis;
    staticlight1();
    bomb();
  }
}







