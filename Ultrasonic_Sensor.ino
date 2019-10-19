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


// Replace these with your WiFi network settings
const char* ssid = "swetx"; //replace this with your WiFi network name
const char* password = "***"; //replace this with your WiFi network password

// defines variables
long duration;
int distance;
String ledColor = "";


CRGB leds[NUM_LEDS];

int brightness = 1; // Initial brightness
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;

void setup() {
  Serial.println("About to try this shit out");

  startMillis = millis();
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

void ledStrip() {
  
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

void ledRed() {
  if ( ledColor != "redThing" ) {
    Serial.println("should do the red thing now");

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Red; FastLED.show(); delay(1);
      FastLED.show();
    }

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black; FastLED.show(); delay(1);
      FastLED.show();
    }
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
      leds[i] = CRGB::Yellow; FastLED.show(); delay(1);
      FastLED.show();
    }

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black; FastLED.show(); delay(1);
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

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black; FastLED.show(); delay(1);
      FastLED.show();
    }
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

  if (distance < 100) {
    int newDistance = measureDistance();
    if ( (newDistance < 100) && (currentMillis - startMillis >= period) ) {
      startMillis = currentMillis;
      int sc = registerPassenger();
      if (sc == 200)
      {
        ledYellow();
        Serial.println("we done got a response and shit");
      }
      else {
        ledRed();
      }
    }
  }
  delay(50);
}
