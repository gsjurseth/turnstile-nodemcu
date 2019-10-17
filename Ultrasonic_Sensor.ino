#include <ESP8266WiFi.h>
#include <stdio.h>
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER

#include <FastLED.h>
#include <ESP8266HTTPClient.h>
// defines pins numbers
const int trigPin = 14;  //D5
const int echoPin = 12;  //D6

#define LED_PIN    4
#define NUM_LEDS 60
#define COLOR_ORDER GRB


// Replace these with your WiFi network settings
const char* ssid = "swetx2.4"; //replace this with your WiFi network name
const char* password = "*****"; //replace this with your WiFi network password

// defines variables
long duration;
int distance;

CRGB leds[NUM_LEDS];

int brightness = 5; // Initial brightness

void setup() {
  Serial.println("About to try this shit out");

  
  /*
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  */
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(115200); // Starts the serial communication

  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());

  
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  //FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_COUNT);
  FastLED.setBrightness(brightness);
  ledBlue();
}

void ledRed() {
  Serial.println("should do the red thing now");

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red; FastLED.show(); delay(5);
    FastLED.show();
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black; FastLED.show(); delay(5);
    FastLED.show();
  }
}

void solidGreen() {
  Serial.println("solid green");

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Green; FastLED.show(); delay(5);
    FastLED.show();
  }
}


void ledGreen() {
  Serial.println("should do the green thing now");

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Green; FastLED.show(); delay(5);
    FastLED.show();
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black; FastLED.show(); delay(5);
    FastLED.show();
  }
}


void ledYellow() {
  Serial.println("should do the yellow thing now");

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Yellow; FastLED.show(); delay(5);
    FastLED.show();
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black; FastLED.show(); delay(5);
    FastLED.show();
  }
}

void ledBlue() {
  Serial.println("should do the blue thing now");

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Blue; FastLED.show(); delay(5);
    FastLED.show();
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black; FastLED.show(); delay(5);
    FastLED.show();
  }
}


void loop() {

  solidGreen();
  // Clears the trigPin
  Serial.println("About to try measure distance");
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  Serial.print("Duration: ");
  Serial.println(duration);

  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if ((WiFi.status() == WL_CONNECTED) && distance < 100)
  {
    ledYellow();
    HTTPClient http; //Object of class HTTPClient
    http.begin("http://emea-poc15-test.apigee.net/demo/ip");
    int httpCode = http.GET();

    if (httpCode == 200)
    {
      ledYellow();
      Serial.println("we done got a response and shit");
      /*

      */
    }
    else {
      ledRed();
    }
    http.end(); //Close connection
  }

  delay(2000);
}
