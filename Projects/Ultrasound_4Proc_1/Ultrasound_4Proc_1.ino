#include <NewPing.h>

#define ECHOPIN 7      
#define TRIGPIN 8
#define MAX_DISTANCE 200

NewPing sonar(TRIGPIN, ECHOPIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup()
{
  Serial.begin(57600);

  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
}

//
//float Distance ()
//{
//  digitalWrite(TRIGPIN, LOW);
//  delayMicroseconds(2);
//  digitalWrite(TRIGPIN, HIGH);
//  delayMicroseconds(30);
//  digitalWrite(TRIGPIN, LOW);
//
//  float distance = pulseIn(ECHOPIN, HIGH);
//  distance = distance / 58;
//  return (distance);
//}

void loop()
{
   delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
}


