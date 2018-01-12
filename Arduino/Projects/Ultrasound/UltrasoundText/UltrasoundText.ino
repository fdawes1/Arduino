#include <NewPing.h>
#include <avr/pgmspace.h>
#include "Charliplexing.h"

#define TRIGGER_PIN  A0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm

int num;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// ----------------------------------Setup------------------------------------------------------ //
void setup()
{
  Serial.begin(115200);
  LedSign::Init(DOUBLE_BUFFER);
}
// ----------------------------------End-Of-Setup------------------------------------------------------ //
void loop()
{
  LedSign::Clear();   //clear the non-acive screen
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Distance: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range) NOTE: will produce unreliable results below 6cm
  Serial.println("");




  numcheck();
}

void numcheck()
{
  int Val = sonar.ping_cm();

  num = map(Val, 0, 90, 0, 90);
  switch (num) {
    case'0':
      {   {0, 14, 17, 25, 21, 19, 17, 14, 0},
        {18000};
      }
    case'1':
      {   {0, 4, 6, 4, 4, 4, 4, 14, 0},
        {18000};
      }
    case'2':
      {   {0, 14, 17, 16, 8, 4, 2, 31, 0},
        {18000};
      }
    case'3':
      {    {0, 31, 8, 4, 8, 16, 17, 14, 0},
        {18000};
      }
    case'4':
      {   {0, 8, 12, 10, 9, 31, 8, 8, 0},
        {18000};
      }
    case'5':
      {
        {0, 31, 1, 15, 16, 16, 17, 14, 0},
        {18000};
      }
  }

}

// use cases?
// massive if statements?

// banner doesnt work as it gives around a 4second delay between each reading.

// case 1 - 90 ? for each possible value of the distance read?

// combine bars lit and number shown into 1 program using different functions??--> remmeber direction from lights.


