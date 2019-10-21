#include <ESP8266WiFi.h>
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER

#include <FastLED.h>
#include <ESP8266HTTPClient.h>

// defines pins numbers
const int trigPin = 14;  //D5
const int echoPin = 12;  //D6

#define LED_PIN    4
#define NUM_LEDS 60
#define COLOR_ORDER GRB
#define ACTIVATE_DISTANCE 50


// Replace these with your WiFi network settings
const char* ssid = "<yourssid"; //replace this with your WiFi network name
const char* password = "<yourpass>"; //replace this with your WiFi network password

// defines variables
long duration;
int distance;
String ledColor = "";


CRGB leds[NUM_LEDS];

int brightness = 30; // Initial brightness
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void setup() {
  Serial.println("About to try this shit out");

  startMillis = millis();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200); // Starts the serial communication

  WiFi.begin(ssid, password);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  //FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_COUNT);
  FastLED.setBrightness(brightness);

  ledBlack();
  RGBLoop();
  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    CylonBounce(0xff, 0, 0, 4, 10, 50);
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());

  rainbowWithGlitter();
  delay(100);
  rainbowWithGlitter();
  delay(100);
  rainbowWithGlitter();
  delay(100);
  rainbowWithGlitter();
  delay(100);
  rainbowWithGlitter();
  delay(1000);
  
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NUM_LEDS);
  setPixel(Pixel,red,green,blue);
  showStrip();
  delay(SpeedDelay);
  setPixel(Pixel,0,0,0);
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

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

// Shamelessly stolen from: https://raw.githubusercontent.com/FastLED/FastLED/master/examples/DemoReel100/DemoReel100.ino
void rainbow() {
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
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

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void solidGreen() {
  if ( ledColor != "green" ) {
    Serial.println("solid green");
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Green; FastLED.show(); delay(1);
      FastLED.show();
    }
  ledColor = "green";    
  }
}

void ledBlack() {
  if ( ledColor != "blackThing" ) {
    Serial.println("should do the black thing now");
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black; FastLED.show();
    }
    FastLED.show();
    ledColor = "blackThing";
  }
}


void ledRed() {
  if ( ledColor != "redThing" ) {
    Serial.println("should do the red thing now");

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Red; FastLED.show();
    }
    FastLED.show();

    delay(200);

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black; FastLED.show();
    }
    FastLED.show();
    ledColor = "redThing";
  }
}

void ledGreen() {
  if ( ledColor != "greenThing" ) {
    Serial.println("should do the green thing now");

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Green; FastLED.show(); delay(1);
      FastLED.show();
    }

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black; FastLED.show(); delay(1);
      FastLED.show();
    }
    ledColor = "greenThing";
  }
}


void ledYellow() {
  if ( ledColor != "yellowThing" ) {
    Serial.println("should do the yellow thing now");
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Yellow; FastLED.show();
      FastLED.show();
    }

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black; FastLED.show();
      FastLED.show();
    }
    ledColor = "yellowThing";
  }
}

void ledBlue() {
  if ( ledColor != "blueThing" ) {
    Serial.println("should do the blue thing now");

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Blue; FastLED.show(); delay(1);
      FastLED.show();
    }

    /*
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black; FastLED.show(); delay(1);
      FastLED.show();
    }
    */
    ledColor = "blueThing";
  }
}


int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;
}

int registerPassenger() {
      HTTPClient http; //Object of class HTTPClient
      http.begin("http://emea-poc15-test.apigee.net/demo/ip");
      int httpCode = http.GET();
      http.end(); //Close connection
      return httpCode;  
}

void loop() {
  int distance;

  solidGreen();
  // Clears the trigPin

  distance = measureDistance();
      
  currentMillis = millis();  //get the current time

  if (distance < ACTIVATE_DISTANCE) {
    int newDistance = measureDistance();
    if ( (newDistance < ACTIVATE_DISTANCE) && (currentMillis - startMillis >= period) ) {
      startMillis = currentMillis;
      int sc = registerPassenger();
      if (sc == 200)
      {
        ledYellow();
        //Sparkle(0xff, 0xff, 0xff, 0);
        Serial.println("we done got a response and shit");
      }
      else {
        Strobe(0xff, 0x00, 0x00, 10, 50, 1000);
        ledGreen();
        //ledRed();
      }
    }
  }
  delay(50);
}
