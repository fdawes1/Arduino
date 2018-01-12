#include "Charliplexing.h"
#include "Font.h"
#include "Arduino.h"
#include <avr/pgmspace.h>
#include <stdlib.h>


#include <NewPing.h>

NewPing sonar(A0, A1, 100); // NewPing setup (Trigg, Echo, Distance(max 400-500))

void setup()
{
  Serial.begin(9600);
  LedSign::Init();
}

void loop()
{
  LedSign::Clear();

  int num = sonar.ping_cm();
  
  String temp = String(num, DEC);
  
  Serial.println(temp);
  
  for (int i = 0; i < temp.length(); i++)
  {
    Font::Draw(temp.charAt(0), 1, 0);
    Font::Draw(temp.charAt(1), 8, 0);
  }
  delay(100);
}
