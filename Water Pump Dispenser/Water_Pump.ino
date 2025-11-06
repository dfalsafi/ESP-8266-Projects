// Pin definitions
const int trigPin = 10;
const int echoPin = 11;
const int relayPin = 7;

// Distance threshold (in cm)
const int distanceThreshold = 10;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Pump OFF initially

  Serial.begin(9600);
}

void loop() {
  long duration;
  int distance;

  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  duration = pulseIn(echoPin, HIGH);

  // Convert to distance in cm
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > distanceThreshold || distance <= 0) {
    // No hand, turn on pump
    Serial.println("No hand detected - Pump ON");
    digitalWrite(relayPin, HIGH);
  } else {
    // Hand is close, turn off pump
    Serial.println("Hand detected - Pump OFF");
    digitalWrite(relayPin, LOW);
  }

  delay(200); // Small delay to reduce bouncing
}