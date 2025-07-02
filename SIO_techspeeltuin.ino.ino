#include <Adafruit_NeoPixel.h>

// Aantal LEDs in je strip:
#define NUM_LEDS 10

// Pin waar de datakabel (R) van de LED-strip op zit:
#define LED_PIN 6

// Ultrasoon sensor pinnen:
#define TRIG_PIN 10
#define ECHO_PIN 11

// Strip-object aanmaken:
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  strip.begin();
  strip.show(); // Alle LEDs uit bij start
}

void loop() {
  long duration;
  float distance;

  // Ultrasoon trigger puls:
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Echo-tijd meten:
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2.0; // Omrekenen naar cm

  Serial.print("Afstand: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Maximale afstand die we willen meten (bijv. 50 cm)
  int maxDistance = 50;

  // Beperk de afstandswaarde tot binnen bereik:
  if (distance > maxDistance) distance = maxDistance;
  if (distance < 0) distance = 0;

  // Bepaal hoeveel LEDs aan moeten, hoe dichterbij hoe meer:
  int ledsAan = map(distance, maxDistance, 0, 0, NUM_LEDS);

  // LEDs instellen:
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < ledsAan) {
      strip.setPixelColor(i, strip.Color(0, 150, 0)); // Groen
    } else {
      strip.setPixelColor(i, 0); // Uit
    }
  }
  strip.show();

  delay(100); // Kleine vertraging
}
