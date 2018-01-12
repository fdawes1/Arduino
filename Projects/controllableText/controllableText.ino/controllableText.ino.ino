
#include "Charliplexing.h"
#include "Myfont.h"
#include "Arduino.h"
bool stringComplete = false;
char inputString;
register  int c;

/* -----------------------------------------------------------------  */
/** MAIN program Setup
*/
void setup()
{
  Serial.begin(9600);
  Serial.println("Serial conection started, waiting for text...");
  LedSign::Init();
}
/* -----------------------------------------------------------------  */
/** MAIN program Loop
*/

void loop()
{
  if (stringComplete)
  {
    Serial.println(inputString);
    c = (unsigned char)*inputString++;

    Myfont::Banner(10, inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

}


void serialEvent()
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n')
    {
      stringComplete = true;
    }
  }
}
