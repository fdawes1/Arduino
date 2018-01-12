#include "Charliplexing.h"
#include "Font.h"
#include "Arduino.h"
#include <avr/pgmspace.h>
#include <NewPing.h>

#define TRIGGER_PIN  A0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

/* -----------------------------------------------------------------  */
/** MAIN program Setup
*/
void setup()
{
  Serial.begin(9600);
  LedSign::Init();
}

/* -----------------------------------------------------------------  */
/** MAIN program Loop
*/
//static const char test[]="12 ";

void loop()
{

  for (int8_t x = DISPLAY_COLS, i = 0;; x--) {
    LedSign::Clear();

    Serial.print("Distance: ");
    Serial.print(sonar.ping_cm());
    Serial.println("cm ");

    char num = sonar.ping_cm();

    char test[] = {num };

    for (int8_t x2 = x, i2 = i; x2 < DISPLAY_COLS;)
    {
      int8_t w = Font::Draw(test[i2], x2, 0);
      x2 += w, i2 = (i2 + 1) % strlen(test);
      if (x2 <= 0)	// off the display completely?
        x = x2, i = i2;
    }
    delay(80);
  }
}
