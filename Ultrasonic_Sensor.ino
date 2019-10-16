#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
// defines pins numbers
const int trigPin = 14;  //D5
const int echoPin = 12;  //D6

// Replace these with your WiFi network settings
const char* ssid = "FancySSID"; //replace this with your WiFi network name
const char* password = ""; //replace this with your WiFi network password

// defines variables
long duration;
int distance;

void setup() {
  Serial.println("About to try this shit out");
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

void loop() {
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
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

  if ((WiFi.status() == WL_CONNECTED) && distance < 100) 
  {
    HTTPClient http; //Object of class HTTPClient
    http.begin("http://emea-poc15-test.apigee.net/demo/ip");
    int httpCode = http.GET();

    if (httpCode > 0) 
    {
      Serial.println("we done got a response and shit");
    }
    http.end(); //Close connection
  }

delay(2000);
}
