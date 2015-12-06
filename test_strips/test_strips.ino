/* Max's Word Clock
 * v1.0
 * 28 November 2015
 *  
 * onetwofoursix
 * fivesevennine
 * eightthreeten
 * eleventwelveo
 * thirfifteenMA
 * twenfortyfour
 * oneseventhree
 * twofiveeightX
 * sixtenelevenM
 * ninetwelveapm
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN1            6
#define PIN2            5
#define NUMPIXELS       6

const int delayVal = 1000;

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  strip1.begin();
  strip2.begin();

}

void loop() {
//theWave();
  theDad();
}

void theWave() {
  for (int i=0 ; i<NUMPIXELS ; i++) {
    strip1.setPixelColor(i, strip1.Color(0,0,63)); // Moderately bright green color.
    strip1.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal);
  }
  for (int i=0 ; i<NUMPIXELS ; i++) {
    strip2.setPixelColor(i, strip2.Color(0,0,63)); // Moderately bright green color.
    strip2.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal);
  }
  for (int i=0 ; i<NUMPIXELS ; i++) {
    strip1.setPixelColor(i, strip1.Color(0,0,0)); // Moderately bright green color.
    strip1.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal);
  }
  for (int i=0 ; i<NUMPIXELS ; i++) {
    strip2.setPixelColor(i, strip2.Color(0,0,0)); // Moderately bright green color.
    strip2.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal);
  }
}

void theDad() {
  
strip2.setPixelColor(1, strip2.Color(0,70,0)); // Moderately bright green color.
    strip2.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal);
strip2.setPixelColor(1, strip2.Color(0,0,0)); // Moderately bright green color.
strip2.setPixelColor(2, strip2.Color(0,70,0)); // Moderately bright green color.
strip2.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal); 
    strip2.setPixelColor(2, strip2.Color(0,0,0)); // Moderately bright green color.
strip1.setPixelColor(3, strip1.Color(0,70,0)); // Moderately bright green color.
strip2.show(); // This sends the updated pixel color to the hardware.
strip1.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal); 
strip1.setPixelColor(3, strip1.Color(0,0,0)); // Moderately bright green color.
strip1.setPixelColor(0, strip1.Color(0,70,0)); // Moderately bright green color.
strip1.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal); 
strip1.setPixelColor(0, strip1.Color(0,0,0)); // Moderately bright green color.
strip1.setPixelColor(3, strip1.Color(0,70,0)); // Moderately bright green color.
strip1.show(); // This sends the updated pixel color to the hardware.
    delay(delayVal); 
strip1.setPixelColor(3, strip1.Color(0,0,0)); // Moderately bright green color.
strip1.show(); // This sends the updated pixel color to the hardware.
 delay(delayVal);
}

