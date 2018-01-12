/*todo
  + map keyboard ascii values to lights -- each key (choose 90) turns on an LED and then dims after 1/2/3 seconds
  + See if CPU temp is avaialble on TheBeast
*/

// INCLUDES--------------------------------------------------------------------------------

#include <FastLED.h>
#include <stdlib.h>

// DEFINES--------------------------------------------------------------------------------

#define NUM_LEDS 120
#define DATA_PIN 2
#define COLOUR_ORDER GRB
#define CHIPSET  WS2812B
#define MAX_BRIGHTNESS 120     // Thats full on, watch the power!
#define MIN_BRIGHTNESS 33      // set to a minimum of 25%

#define FORWARD 0

#define COOLING  40 //Less cooling = taller flames.  More cooling = shorter flame, suggested range 20-10
#define SPARKING 80 //lower chance = more flickery fire, suggested range 50-200.
#define FRAMES_PER_SECOND 60

// INITS--------------------------------------------------------------------------------
CRGB leds[NUM_LEDS];

//CRGBArray<NUM_LEDS> leds;   //initialising like this allows use of (CURRENTLY UNUSED) FastLed Functions

CRGBPalette16 gPal;

// VARIABLES--------------------------------------------------------------------------------


int prog = 0;
int dire = 0;
int brightnessValue;


boolean direction = FORWARD;

String src_msg = "";

int msgProg = 0;

int msgHue1R;
int msgHue1G;
int msgHue1B;
int msgHue1;

//add more Hues if needed
int msgDire;
int msgPeak;
int msgCount;
int msgBrightness;
int msgTime;

int FuncHue;
int randHue;

int peakVal;

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

//Timer Stuff

int Delay;


//SETUP--------------------------------------------------------------------------------
void setup()
{
  FastLED.delay( 2000 ); // power-up safety delay
  FastLED.addLeds<WS2812B, DATA_PIN, COLOUR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  // FastLED.setBrightness( MAX_BRIGHTNESS );
  FastLED.setDither(0);

  Serial.begin(9600);

  pinMode(13, OUTPUT);
}
// MAIN--------------------------------------------------------------------------------
void loop()
{

  DIRECTION();
  program();

  FastLED.setBrightness( msgBrightness );

}

//FUNCTIONS--------------------------------------------------------------------------------
void program ()
{

  /*
    Programs
     0 = Solid Colour -- Changeable Hue
     1= Breathe -- Changeable Hue(Multiple / Random) & Breath Rate
     2= Fire -- Changeable Hue
     3= Chase / Comet
     4= juggle
     5= Rainbow
     6= BPM
     7= Time Of Light
     10 = peak Detection (random pos)


  */

  if (msgProg == 0)
  {
    //FuncHue =  CRGB(msgHue1R, msgHue1G, msgHue1B);
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB(msgHue1R, msgHue1G, msgHue1B);// CHSV(FuncHue, 255, 255 );
    }
  }

  if (msgProg == 1)
  {
    // int breathColour =  CRGB(msgHue1R, msgHue1G, msgHue1B);
    int  breathRate = msgCount * 1000.0; //(rate * Delay) -- 1000 = 1 second

    if (direction == FORWARD)
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CRGB(msgHue1R, msgHue1G, msgHue1B);// CHSV(breathColour, 255, 255);
      }
    }
    else
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CHSV(randHue, 255, 255);
      }
    }

    int BrightnessMaxVal = msgBrightness * 1.4; //max 140
    float breathlight = (exp(sin(millis() / (msgCount * 1000.0) * PI)) - 0.36787944) * 108.0;

    if (breathlight <= 1 )
    {
      randHue = random(230);
    }

    FastLED.setBrightness(constrain(breathlight, 0, BrightnessMaxVal));
    FastLED.show();
  }

  if (msgProg == 2)
  {
    FuncHue = msgHue1;

    CRGB darkcolour  = CHSV(FuncHue, 255, 192); // pure hue, three-quarters brightness
    CRGB lightcolour = CHSV((FuncHue - 25), 128, 200); // half 'whitened', full brightness
    gPal = CRGBPalette16( CRGB::Black, darkcolour, lightcolour, CRGB::White);


    // Add entropy to random number generator
    random16_add_entropy( random());

    Fire2012WithPalette(); // run simulation using palette colors

    FastLED.show(); // display this frame
    FastLED.delay(1000 / FRAMES_PER_SECOND);
  }

  if (msgProg == 3)
  {
    FuncHue =  msgHue1;
    Delay = msgCount + 10 ;
    if (direction == FORWARD)
    {

      fadeToBlackBy( leds, NUM_LEDS, 50);
      int pos = beatsin16(Delay, 0, NUM_LEDS);
      leds[pos] += CRGB(msgHue1R, msgHue1G, msgHue1B);
      FuncHue += 25;
      leds[(3 * pos) / 4] += CRGB(msgHue1R, msgHue1G, msgHue1B);
      FuncHue += 25;
      leds[pos / 2] += CRGB(msgHue1R, msgHue1G, msgHue1B);
      FuncHue += 25;
      leds[pos / 4] += CRGB(msgHue1R, msgHue1G, msgHue1B);
    }

    else {
      fadeToBlackBy( leds, NUM_LEDS, 5);
      int pos = beatsin16(Delay, 0, NUM_LEDS);
      leds[pos] += CHSV(FuncHue + (4 * pos), 255, 192);
    }
    FastLED.show();
  }

  if (msgProg == 4)
  {
    fadeToBlackBy( leds, NUM_LEDS, 20);
    byte dothue;
    int numDots = msgCount;
    dothue =  msgHue1;

    for ( int i = 0; i < numDots; i++)
    {
      leds[beatsin16(i + 7, 0, NUM_LEDS)] |= CHSV(dothue, 200, 255);
      dothue += 25;
    }
    FastLED.show();
  }

  if (msgProg == 5)
  {
    FuncHue =  msgHue1;
    uint8_t BeatsPerMinute = msgCount * 10 ;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    for ( int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = ColorFromPalette(palette, FuncHue + (i * 2), beat - FuncHue + (i * 10));
    }
    FastLED.show();
  }

  if (msgProg == 6)
  {
    if (direction == FORWARD)
    {
      fill_rainbow( leds, NUM_LEDS, gHue, msgCount);
    }
    else
    {
      fill_rainbow( leds, NUM_LEDS, gHue, msgCount);
      gHue += 1;
    }
    FastLED.show();
  }

  if (msgProg == 7 )
  {
    // Control Colour of light depending on Time of Day.
    // Midnight Midday = red (12hr format)
 
     FuncHue = map(msgTime, 0, 24, 0, 225);      //can be mapped to 12 hour clock                               

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CHSV(FuncHue, 255, 255 );
    }

  }
  //  progs 8,9

  if (msgProg == 10)
  {
    FuncHue = msgHue1;
    peakVal = msgPeak;

    int width = NUM_LEDS / 10;
    int faderate = 128;
    int posMax = NUM_LEDS - width;
    int posMin = 0 + width;
    int pos = constrain(NUM_LEDS, posMin, posMax);
    int startPoint = random(pos);

    //if (peakVal > 95) //Read by VisualStudio Program
    {
      if (direction == FORWARD) // middle --> out
      {
        int i = startPoint;
        int j = startPoint;
        while ((i <= (startPoint + width)) && (j >= (startPoint - width)) && (j >= 0))
        {
          fadeToBlackBy(leds, NUM_LEDS, faderate);
          leds[i] = FuncHue;
          leds[j] = FuncHue;

          i++;
          j--;
          FuncHue += 15;
          FastLED.delay(25);
        }
      }
      else // out --> middle
      {
        int i = startPoint + width;
        int j = startPoint - width;
        while ((i >= (startPoint)) && (j <= (startPoint)) && (j >= 0))
        {
          fadeToBlackBy(leds, NUM_LEDS, faderate);
          leds[i] = FuncHue;
          leds[j] = FuncHue;

          i--;
          j++;
          FuncHue += 15;
          FastLED.delay(25);
        }
        //      }
      }
    }
    FastLED.show();
  }

  FastLED.show();// leave at bottom
}
// End of Program--------------------------------------------------------------------------------

void DIRECTION()
{
  dire = msgDire;

  if (dire == 0)
  {
    direction = FORWARD;
  }

  else if (dire == 1)
  {
    direction = !FORWARD;
  }
}//End of DIRECTION()--------------------------------------------------------------------------------



void Fire2012WithPalette()
{
  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++)
  {
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--)
  {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if ( random8() < SPARKING )
  {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160, 255) );
  }

  // Step 4.  Map from heat cells to LED colors
  for ( int j = 0; j < NUM_LEDS; j++)
  {
    // Scale the heat value from 0-255 down to 0-240
    // for best results with colour palettes.
    byte colourindex = scale8( heat[j], 240);

    CRGB colour = ColorFromPalette( gPal, colourindex);
    int pixelnumber;
    if ( direction == !FORWARD )
    {
      pixelnumber = (NUM_LEDS - 1) - j;

    }
    else
    {
      pixelnumber = j;
    }
    leds[pixelnumber] = colour;



  }
}//End of Fire-------------------------------------------------------------------------------




//----------------------------------- Visual Studio Code ----------------------------------------------------------------------------------------------------------------------


void serialEvent()
{
  if (Serial.available())
  {
    char inChar = (char) Serial.read();
    if (inChar != 'X')
    {
      src_msg += inChar;
    }


    if (inChar == 'X')
    {
      src_msg += inChar;

      /*
        Needed Things:

        Cannot use A-F as Colour will be recieved in HEX
        X = end of msg

        P  1  Program P
        H  2  Colour Choices (2+)             H,J,K,M etc
        I  3  dIrection                       I
        L  4  Peak Level                      L
        N  5  counter Number (balls etc)      N
        R  6  bRightness                      R
        T  7  Time                            T
        X
      */


      msgProg =   getSrcValue(src_msg, 'P', 'H');

      msgHue1R = getSrcValue(src_msg, 'H', 'J');
      msgHue1G = getSrcValue(src_msg, 'J', 'K');
      msgHue1B = getSrcValue(src_msg, 'K', 'M');
      msgHue1 = getSrcValue(src_msg, 'M', 'I');

      msgDire = getSrcValue(src_msg , 'I', 'L');

      msgPeak = getSrcValue (src_msg, 'L', 'N');

      msgCount = getSrcValue (src_msg, 'N', 'R');

      msgBrightness = getSrcValue(src_msg, 'R', 'T');

      msgTime = getSrcValue(src_msg, 'T', 'X');

      src_msg = ""; //clear string awaiting next command
    }
  }
}

int getSrcValue(String src_msg, char c1, char c2)
{
  int c1_pose = src_msg.indexOf(c1);
  int c2_pose = src_msg.indexOf(c2);

  //ERROR HANDLING---------------------
  if (c1_pose > c2_pose)
  {
    int temp = c1_pose;
    c1_pose = c2_pose;
    c2_pose = temp;
  }
  if (c1_pose == -1 || c2_pose == -1)
  {
    return -1;
  }
  //-----------------------------------

  String res = src_msg.substring(c1_pose + 1, c2_pose);
  return atoi(res.c_str());
}


