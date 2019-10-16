#include <ESP8266WiFi.h>
#include <FastLED.h>
#include <ESP8266HTTPClient.h>
// defines pins numbers
const int trigPin = 14;  //D5
const int echoPin = 12;  //D6

#define LED_PIN    2
#define LED_COUNT 60
#define COLOR_ORDER GRB


// Replace these with your WiFi network settings
const char* ssid = "GoogleGuest-Legacy"; //replace this with your WiFi network name
const char* password = ""; //replace this with your WiFi network password

// defines variables
long duration;
int distance;

CRGB leds[LED_COUNT];

int brightness = 5; // Initial brightness

void setup() {
  Serial.println("About to try this shit out");

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_COUNT);
  FastLED.setBrightness(brightness);
  
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
}

void ledWhite() {
  leds[0] = CRGB::White; FastLED.show(); delay(30);
  leds[0] = CRGB::Black; FastLED.show(); delay(30);
  FastLED.show();
  
}

void ledGreen() {
  leds[0] = CRGB::Green; FastLED.show(); delay(30);
  leds[0] = CRGB::Black; FastLED.show(); delay(30);
  FastLED.show();
  
}

void ledRed() {
  for (int i=0;i++;i<60) {
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(10);
  }
}

void ledYellow() {
  leds[0] = CRGB::Yellow; FastLED.show(); delay(30);
  leds[0] = CRGB::Black; FastLED.show(); delay(30);
  FastLED.show();
  
}


void loop() {

  // Clears the trigPin
  Serial.println("About to try measure distance");
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  ledRed();
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

    if (httpCode > 0)
    {
      Serial.println("we done got a response and shit");
      /*
        const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
        DynamicJsonBuffer jsonBuffer(bufferSize);
        JsonObject& root = jsonBuffer.parseObject(http.getString());

        int id = root["id"];
        const char* name = root["name"];
        const char* username = root["username"];
        const char* email = root["email"];

        Serial.print("Name:");
        Serial.println(name);
        Serial.print("Username:");
        Serial.println(username);
        Serial.print("Email:");
        Serial.println(email);
      */
    }
    http.end(); //Close connection
  }

  delay(2000);
  leds[0] = CRGB::Green;
  FastLED.show();
}
