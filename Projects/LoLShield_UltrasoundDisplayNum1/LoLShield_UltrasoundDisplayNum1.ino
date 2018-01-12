#include <avr/pgmspace.h>  //AVR library for writing to ROM
#include <Charliplexing.h> //Imports the library, which needs to be
#include <NewPing.h>

#define TRIGGER_PIN  A0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A1  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


//Sets the time each frame is shown (milliseconds)
const unsigned int blinkdelay = 75;
byte brightness = 4; //Brightness goes from 0-7

int Val;
int num;

PROGMEM const uint16_t BitMap0[][9] = {
  {0, 14, 17, 25, 21, 19, 17, 14, 0}, //48, 0.
};

PROGMEM const uint16_t BitMap1[][9] = {
  {0, 4, 6, 4, 4, 4, 4, 14, 0}, //49, 1
 
};
PROGMEM const uint16_t BitMap2[][9] = {
  {0, 14, 17, 16, 8, 4, 2, 31, 0}, //50, 2

};
PROGMEM const uint16_t BitMap3[][9] = {
  {0, 31, 8, 4, 8, 16, 17, 14, 0}, //51, 3
 
};
PROGMEM const uint16_t BitMap4[][9] = {
  {0, 8, 12, 10, 9, 31, 8, 8, 0}, //52, 4

};
PROGMEM const uint16_t BitMap5[][9] = {
  {0, 31, 1, 15, 16, 16, 17, 14, 0}, //53, 5
 
};
PROGMEM const uint16_t BitMap6[][9] = {
  {0, 12, 2, 1, 15, 17, 17, 14, 0}, //54, 6
 
};
PROGMEM const uint16_t BitMap7[][9] = {
  {0, 31, 16, 8, 4, 2, 2, 2, 0}, //55, 7
 
};
PROGMEM const uint16_t BitMap8[][9] = {
  {0, 14, 17, 17, 14, 17, 17, 14, 0}, //56, 8
 
};
PROGMEM const uint16_t BitMap9[][9] = {
  {0, 14, 17, 17, 30, 16, 8, 6, 0}, //57, 9
 
};

void setup() {
  Serial.begin(9600);
  LedSign::Init(GRAYSCALE);  //Initializes the screen
}
void loop() {
  Serial.print("Distance: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range) NOTE: will produce unreliable results below 6cm
  Serial.println("cm ");

 DisplayBitMap(brightness);  //Displays the bitmap
}

void DisplayBitMap(uint8_t grayscale)
{
  boolean run = true;  //While this is true, the screen updates
  byte frame = 0;      //Frame counter
  byte line = 0;       //Row counter
  unsigned long data;  //Temporary storage of the row data
  unsigned long start = 0;


  num = map(sonar.ping_cm() , 0, 90, 0, 9);

  Serial.print("Display: ");
   Serial.print(num);
  Serial.println("");
 

  switch (num)
  {
    case 0:
      Serial.print(num);
      for (line = 0; line < 9; line++)
      {
        //Here we fetch data from program memory with a pointer.
        data = pgm_read_word_near (&BitMap0[frame][line]);

        //This is where the bit-shifting happens to pull out
        //each LED from a row. If the bit is 1, then the LED
        //is turned on, otherwise it is turned off.
        for (byte led = 0; led < 14; ++led)
        {
          if (data & (1 << led))
          {
            LedSign::Set(led, line, grayscale);
          }
          else
          {
            LedSign::Set(led, line, 0);
          }
        }
      }
      break;

    case 1:
      Serial.print(num);
      for (line = 0; line < 9; line++)
      {
        data = pgm_read_word_near (&BitMap1[frame][line]);

        for (byte led = 0; led < 14; ++led)
        {
          if (data & (1 << led))
          {
            LedSign::Set(led, line, grayscale);
          }
          else
          {
            LedSign::Set(led, line, 0);
          }
        }
      }
      break;
    case 2:
      Serial.print(num);
      for (line = 0; line < 9; line++)
      {
        data = pgm_read_word_near (&BitMap2[frame][line]);

        for (byte led = 0; led < 14; ++led)
        {
          if (data & (1 << led))
          {
            LedSign::Set(led, line, grayscale);
          }
          else
          {
            LedSign::Set(led, line, 0);
          }
        }
      }
      break;
    case 3:
      Serial.print(num);
      for (line = 0; line < 9; line++)
      {
        data = pgm_read_word_near (&BitMap3[frame][line]);

        for (byte led = 0; led < 14; ++led)
        {
          if (data & (1 << led))
          {
            LedSign::Set(led, line, grayscale);
          }
          else
          {
            LedSign::Set(led, line, 0);
          }
        }
      }
      break;

    case 4:
      Serial.print(num);
      for (line = 0; line < 9; line++)
      {
        data = pgm_read_word_near (&BitMap4[frame][line]);

        for (byte led = 0; led < 14; ++led)
        {
          if (data & (1 << led))
          {
            LedSign::Set(led, line, grayscale);
          }
          else
          {
            LedSign::Set(led, line, 0);
          }
        }
      }
      break;

    case 5:
      Serial.print(num);
      for (line = 0; line < 9; line++)
      {
        data = pgm_read_word_near (&BitMap5[frame][line]);

        for (byte led = 0; led < 14; ++led)
        {
          if (data & (1 << led))
          {
            LedSign::Set(led, line, grayscale);
          }
          else
          {
            LedSign::Set(led, line, 0);
          }
        }
      }
      break;

    case 6:
      Serial.print(num);
      for (line = 0; line < 9; line++)
      {

        data = pgm_read_word_near (&BitMap6[frame][line]);

        for (byte led = 0; led < 14; ++led)
        {
          if (data & (1 << led))
          {
            LedSign::Set(led, line, grayscale);
          }
          else
          {
            LedSign::Set(led, line, 0);
          }
        }
      }
      break;

    case 7:
      Serial.print(num);
      for (line = 0; line < 9; line++)
      {
        data = pgm_read_word_near (&BitMap7[frame][line]);

        for (byte led = 0; led < 14; ++led)
        {
          if (data & (1 << led))
          {
            LedSign::Set(led, line, grayscale);
          }
          else
          {
            LedSign::Set(led, line, 0);
          }
        }
      }
      break;

    case 8:
      Serial.print(num);
      for (line = 0; line < 9; line++)
      {
        data = pgm_read_word_near (&BitMap8[frame][line]);

        for (byte led = 0; led < 14; ++led)
        {
          if (data & (1 << led))
          {
            LedSign::Set(led, line, grayscale);
          }
          else
          {
            LedSign::Set(led, line, 0);
          }
        }
      }
      break;

    case 9:
      Serial.print(num);
      for (line = 0; line < 9; line++)
      {
        data = pgm_read_word_near (&BitMap9[frame][line]);

        for (byte led = 0; led < 14; ++led)
        {
          if (data & (1 << led))
          {
            LedSign::Set(led, line, grayscale);
          }
          else
          {
            LedSign::Set(led, line, 0);
          }
        }
      }
      break;
  }
  LedSign::Flip(true);

  unsigned long end = millis();
  unsigned long diff = end - start;
  if ( start && (diff < blinkdelay) )
    delay( blinkdelay - diff );
  start = end;

  frame++;

}
