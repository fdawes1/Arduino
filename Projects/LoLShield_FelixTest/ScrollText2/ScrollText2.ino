#include "Charliplexing.h"
#include "Font.h"
#include "Arduino.h"


char message[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.!?@/:;()";
int messageLen = sizeof(message);
int displayLen = 13;

/* -----------------------------------------------------------------  */
/** MAIN program Setup
 */
void setup()                    // run once, when the sketch starts
{
  LedSign::Init(DOUBLE_BUFFER);
}

/* -----------------------------------------------------------------  */
/** MAIN program Loop
 */
void loop()                     // run over and over again
{
  int nextPos;

  int nextRow = 0;
  int brightness = 0;
  
  // Position loop
  for (int offset = displayLen; nextPos > 0; offset--) {
    LedSign::Clear();
    
    nextPos = offset;
    
    // Character draw loop
    for (int i = 0; i < messageLen; i++) {
      int charLen = Font::Draw(message[i], nextPos, nextRow); 
      Font::Draw(message[i], nextPos, nextRow+9); 
      nextPos += charLen;      
    }

    LedSign::Flip();
    delay(80);

    LedSign::SetBrightness(abs(brightness));
    
    brightness += 10;
    if (brightness >= 127) { brightness = -127; }
    
//    nextRow++;
    if (nextRow > 1) { nextRow = -7; }
  }
}
