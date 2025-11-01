#define BLYNK_TEMPLATE_ID "TMPL2xo9fNxDr"
#define BLYNK_TEMPLATE_NAME "Janga Janga"
#define BLYNK_AUTH_TOKEN "2N2iZcFInb2q4CoY4pwhAAALhH8ZekY-"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <NewPing.h>

// Your WiFi credentials
char ssid[] = "iPhone";   // Replace with your WiFi Name
char pass[] = "Danyal2005";  // Replace with your WiFi password

// Ultrasonic Sensor pins

#define ECHO_PIN D2     // D2
#define TRIGGER_PIN D1 // D1
#define MAX_DISTANCE 200  // Maximum distance we want to measure (in centimeters)

// Initialize NewPing library
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

BlynkTimer timer;

void setup() {
  // Debug console
  Serial.begin(115200);

  // Connect to Wi-Fi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void sendSensor() {
  // Measure distance
  unsigned int distance = sonar.ping_cm();

  // Send distance to Blynk app
  Blynk.virtualWrite(V0, distance);  // Gauge widget
  Blynk.virtualWrite(V1, distance);  // Label widget

  // Print distance to Serial Monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
void loop() {
  Blynk.run();
  timer.run();  // Initiates BlynkTimer
}
