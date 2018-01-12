// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include <Charliplexing.h>
#include <avr/pgmspace.h>

#define TRIGGER_PIN  A0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int8_t x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, y1;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  LedSign::Init(DOUBLE_BUFFER);

  x1 = 1;
  x2 = 2;
  x3 = 3;
  x4 = 4;
  x5 = 5;
  x6 = 6;
  x7 = 7;
  x8 = 8;
  x9 = 9;
  x10 = 10;
  x11 = 11;
  x12 = 12;
  x13 = 13;
  x14 = 0;

} // ----------------------------------End-Of-Setup------------------------------------------------------ //

void loop() {
  LedSign::Clear();   //clear the non-acive screen
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Distance: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range) NOTE: will produce unreliable results below 6cm
  Serial.println("");

  int xVal = sonar.ping_cm();

  y1 = map(xVal, 0, 90, 0, 9);

  for (int led = 0; led < y1; led++)
  {
    LedSign::Set(x1, led, 1);
    LedSign::Set(x1, led, 1);
    LedSign::Set(x2, led, 1);
    LedSign::Set(x3, led, 1);
    LedSign::Set(x4, led, 1);
    LedSign::Set(x5, led, 1);
    LedSign::Set(x6, led, 1);
    LedSign::Set(x7, led, 1);
    LedSign::Set(x8, led, 1);
    LedSign::Set(x9, led, 1);
    LedSign::Set(x10, led, 1);
    LedSign::Set(x11, led, 1);
    LedSign::Set(x12, led, 1);
    LedSign::Set(x13, led, 1);
    LedSign::Set(x14, led, 1);

    LedSign::Flip();
  }
  delay(100); // This delay allows LED to be seen clearly.

}
