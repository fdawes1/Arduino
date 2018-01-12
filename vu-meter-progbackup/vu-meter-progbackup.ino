void program ()
{
  FastLED.clear(); //refresh strips

  brightnessValue = msgBrightness + 10;
  FastLED.setBrightness(constrain(brightnessValue, MIN_BRIGHTNESS, MAX_BRIGHTNESS));

  int valleft = analogRead(A1); //audio left
  int valright = analogRead(A0); //audio right

  sensitivity = msgSens * 20; // careful with max sensitivity --> causes too much power to be pulled and crashes system.

  int numLedsToLightleft = map(valleft, 0, sensitivity, 0, NUM_LEDS);     //sensitivity was 450
  int numLedsToLightright = map(valright, 0, sensitivity, 0, NUM_LEDS);   //sensitivity was 450

  if (prog == 0)//normal
  {
    for (int led = 0; led < numLedsToLightleft; led++)
    {
      mappedHue = msgHue;
      if (direction == FORWARD)
      {
        ledsleft[led] = CHSV(mappedHue, 255, 255);
      }
      else
      {
        ledsleft[NUM_LEDS - 1 - led] = CHSV(mappedHue, 255, 255);
      }
    }
    for (int led = 0; led < numLedsToLightright; led++)
    {
      mappedHue = msgHue;
      if (direction == FORWARD)
      {
        ledsright[led] = CHSV(mappedHue, 255, 255);
      }
      else
      {
        ledsright[NUM_LEDS - 1 - led] = CHSV(mappedHue, 255, 255);
      }
    }
  }

  else  if (prog == 1)//random colours
  {
    static uint8_t hue;
    for (int led = 0; led < numLedsToLightleft; led++)
    {
      mappedHue = msgHue;
      if (direction == FORWARD)
      {
        ledsleft.fadeToBlackBy(40); // hold colour for longer making it more visually appealing
        ledsleft[led] = CHSV(hue++, 255, 255);
      }
      else
      {
        ledsleft.fadeToBlackBy(40);
        ledsleft[NUM_LEDS - 1 - led] =  CHSV(hue++, 255, 255);
      }
    }
    for (int led = 0; led < numLedsToLightright; led++)
    {
      mappedHue = msgHue;
      if (direction == FORWARD)
      {
        ledsright.fadeToBlackBy(40);
        ledsright[led] = CHSV(hue++, 255, 255);
      }
      else
      {
        ledsright.fadeToBlackBy(40);
        ledsright[NUM_LEDS - 1 - led] =  CHSV(hue++, 255, 255);
      }
    }
  }

  else  if (prog == 2)//normal + rainbow/scrollable
  {
    mappedHueleft = msgHue;
    mappedHueright = msgHue;

    for (int led = 0; led < (numLedsToLightleft); ++led)
    {
      if (direction == FORWARD)
      {
        ledsleft[led] = (led - NUM_LEDS - 1, led, 0, CHSV(mappedHueleft, 240, 240));
        mappedHueleft += 5;
      }
      else
      {
        ledsleft[NUM_LEDS - 1 - led] = (led - (NUM_LEDS / 2) - 1, led, 0, CHSV(mappedHueleft, 240, 240));
        mappedHueleft += 5;
      }
    }
    for (int led = 0; led < (numLedsToLightright); ++led)
    {
      if (direction == FORWARD)
      {
        ledsright[led] = (led - (NUM_LEDS) - 1, led, 0, CHSV(mappedHueright, 240, 240));
        mappedHueright += 5;
      }
      else
      {
        ledsright[NUM_LEDS - 1 - led] = (led - (NUM_LEDS / 2) - 1, led, 0, CHSV(mappedHueright, 240, 240));
        mappedHueright += 5;
      }
    }
  }

  else if (prog == 3) //outer->> middle & middle --> outer
  {

    int Mvalleft = analogRead(A1); //audio left
    int Mvalright = analogRead(A0); //audio right

    sensitivity = msgSens * 20; // careful with max sensitivity --> causes too much power to be pulled and crashes system.

    int MnumLedsToLightleft = map(Mvalleft, 0, sensitivity, 0, NUM_LEDS);  //sensitivity was 600
    int MnumLedsToLightright = map(Mvalright, 0, sensitivity, 0, NUM_LEDS); //sensitivity was 600

    mappedHueleft = msgHue;
    mappedHueright = msgHue;

    if (direction == FORWARD)
    {
      for (int led = 0; led < (MnumLedsToLightleft); ++led)
      {
        ledsleft[led] = (led - (NUM_LEDS / 2) - 1, led, 0, CHSV(mappedHueleft, 240, 240));
        ledsleft[NUM_LEDS - 1 - led] = (led - (NUM_LEDS / 2) - 1, led, 0, CHSV(mappedHueleft, 240, 240));
        mappedHueleft += 5;
      }
      for (int led = 0; led <  MnumLedsToLightright; ++led)
      {
        ledsright[led] = (led - (NUM_LEDS / 2) - 1, led, 0, CHSV(mappedHueright, 240, 240));
        ledsright[NUM_LEDS - 1 - led] = (led - (NUM_LEDS / 2) - 1, led, 0, CHSV(mappedHueright, 240, 240));
        mappedHueright += 5;
      }
    }
    else
    {
      for (int led = 15; led < (MnumLedsToLightleft + 15); ++led)
      {
        ledsleft[led] = (led - (NUM_LEDS / 2) - 1, led, 0, CHSV(mappedHueleft, 240, 240));
        ledsleft[NUM_LEDS - 1 - led] = (led - (NUM_LEDS / 2) - 1, led, 0, CHSV(mappedHueleft, 240, 240));
        mappedHueleft += 5;
      }

      for (int led = 15; led <  (MnumLedsToLightright + 15); ++led)
      {
        ledsright[led] = (led - (NUM_LEDS / 2) - 1, led, 0, CHSV(mappedHueright, 240, 240));
        ledsright[NUM_LEDS - 1 - led] = (led - (NUM_LEDS / 2) - 1, led, 0, CHSV(mappedHueright, 240, 240));
        mappedHueright += 5;
      }
    }
  }

  else if (prog == 4) // Beat Detection -- single
  {
    static uint8_t hue;
    sensitivity = msgSens * 15;
    int valleft = analogRead(A1); //audio left
    int valright = analogRead(A0); //audio left
    int numLedsToLightleft = map(valright, 0, sensitivity, 0, NUM_LEDS);
    int numLedsToLightright = map(valright, 0, sensitivity, 0, NUM_LEDS);
    int faderate = msgBallCount ;
    mappedHueleft = msgHue;
    mappedHueright = msgHue;



    if ((numLedsToLightleft > (NUM_LEDS / 2) - 1) && (numLedsToLightright > (NUM_LEDS / 2) - 1)) // using both audio channels removes pulses from unwanted instruments in only 1 ear
    {
      if (direction == FORWARD)
      {
        for (int i = 0; i  < (NUM_LEDS); i++)
        {
          // fade everything out
          ledsleft.fadeToBlackBy(faderate);
          ledsright.fadeToBlackBy(faderate);


          //setled value
          ledsleft[i] = CHSV(mappedHueleft, 255, 255);
          ledsright[i] = CHSV(mappedHueright, 255, 255);
          mappedHueleft += 5;
          mappedHueright += 5;
          FastLED.delay(15);
        }
      }
      else {
        for (int i = 0; i  < (NUM_LEDS); i++)
        {
          // fade everything out
          ledsleft.fadeToBlackBy(faderate);
          ledsright.fadeToBlackBy(faderate);


          //setled value
          ledsleft[NUM_LEDS - 1 - i] = CHSV(mappedHueleft, 255, 255);
          ledsright[NUM_LEDS - 1 - i] = CHSV(mappedHueright, 255, 255);
          mappedHueleft += 5;
          mappedHueright += 5;
          FastLED.delay(15);
        }
      }
    }


  }

  else if (prog == 5) //beat detection -- double
  {

    static uint8_t hue;
    sensitivity = msgSens * 15;
    int valleft = analogRead(A1); //audio left
    int valright = analogRead(A0); //audio left
    int numLedsToLightleft = map(valright, 0, sensitivity, 0, NUM_LEDS);     //sensitivity was 450
    int numLedsToLightright = map(valright, 0, sensitivity, 0, NUM_LEDS);     //sensitivity was 450
    int faderate =   msgBallCount ;
    mappedHueleft = msgHue;
    mappedHueright = msgHue;

    if ((numLedsToLightleft > (NUM_LEDS / 2) - 1) && (numLedsToLightright > (NUM_LEDS / 2) - 1)) // using both audio channels removes pulses from unwanted instruments in only 1 ear
    {
      if (direction == FORWARD)
      {
        for (int i = 0; i  < (NUM_LEDS / 2 ); i++)
        {
          // fade everything out
          ledsleft.fadeToBlackBy(faderate);
          ledsright.fadeToBlackBy(faderate);


          //setled value
          ledsleft[(NUM_LEDS / 2) - 1 - i] = CHSV(mappedHueleft, 255, 255);
          ledsright[(NUM_LEDS / 2) - 1 - i] = CHSV(mappedHueright, 255, 255);
          mappedHueleft += 5;
          mappedHueright += 5;

          // copy bottom 15 leds to the top 15 leds,
          ledsleft(NUM_LEDS / 2 , NUM_LEDS - 1) = ledsleft(NUM_LEDS / 2 - 1 , 0);
          ledsright(NUM_LEDS / 2 , NUM_LEDS - 1) = ledsright(NUM_LEDS / 2 - 1 , 0);
          FastLED.delay(15);
        }
      }
      else
      {
        for (int i = 0; i < NUM_LEDS / 2; i++)
        {
          // fade everything out
          ledsleft.fadeToBlackBy(faderate);
          ledsright.fadeToBlackBy(faderate);

          ledsleft[i] = CHSV(mappedHueleft, 255, 255);
          ledsright[i] = CHSV(mappedHueright, 255, 255);
          mappedHueleft += 5;
          mappedHueright += 5;

          ledsleft(NUM_LEDS / 2 , NUM_LEDS - 1) = ledsleft(NUM_LEDS  / 2 - 1 , 0);
          ledsright(NUM_LEDS / 2 , NUM_LEDS - 1) = ledsright(NUM_LEDS  / 2 - 1 , 0);
          FastLED.delay(15);
        }
      }
    }
  }

  else if (prog == 6) // beat detection random position
  {
    mappedHue = msgHue;
    sensitivity = msgSens * 15;
    int faderate = 128;
    int width = 5;
    int posMax = NUM_LEDS - width;
    int posMin = 0 + width;
    int pos = constrain(NUM_LEDS, posMin, posMax);
    int startPoint = random(pos);

    if ((numLedsToLightleft > (NUM_LEDS / 2) - 1) && (numLedsToLightright > (NUM_LEDS / 2) - 1)) // using both audio channels removes pulses from unwanted instruments in only 1 ear
    {
      if (direction == FORWARD) // middle --> out
      {
        int i = startPoint;
        int j = startPoint;
        while ((i <= (startPoint + width)) && (j >= (startPoint - width)) && (j >= 0))
        {
          ledsleft.fadeToBlackBy(faderate);
          ledsright.fadeToBlackBy(faderate);
          ledsleft[i] = CHSV(mappedHue, 255, 255);
          ledsright[i] = CHSV(mappedHue, 255, 255);

          ledsleft[j] = CHSV(mappedHue, 255, 255);
          ledsright[j] = CHSV(mappedHue, 255, 255);

          i++;
          j--;
          mappedHue += 15;
          FastLED.delay(25);
        }
      }
      else // out --> middle
      {
        int i = startPoint + width;
        int j = startPoint - width;
        while ((i >= (startPoint)) && (j <= (startPoint)) && (j >= 0))
        {
          ledsleft.fadeToBlackBy(faderate);
          ledsright.fadeToBlackBy(faderate);
          ledsleft[i] = CHSV(mappedHue, 255, 255);
          ledsright[i] = CHSV(mappedHue, 255, 255);

          ledsleft[j] = CHSV(mappedHue, 255, 255);
          ledsright[j] = CHSV(mappedHue, 255, 255);

          i--;
          j++;
          mappedHue += 15;
          FastLED.delay(25);
        }
      }
    }
  }
  else if (prog == 7)//single
  {
    //audio left-----------------------------------------------

    const int sampleWindowleft = 12.5; // Sample window width in mS (50 mS = 20Hz)
    unsigned int sampleleft;

    int gHue = msgHue;

    unsigned long startMillisleft = millis(); // Start of sample window
    unsigned int peakToPeakleft = 0;   // peak-to-peak level

    unsigned int signalMaxleft = 0;
    unsigned int signalMinleft = 1023;

    // collect data for sample window time (ms)
    while (millis() - startMillisleft < sampleWindowleft)
    {
      sampleleft = analogRead(A1);
      if (sampleleft < 1023)  // toss out spurious readings
      {
        if (sampleleft > signalMaxleft)
        {
          signalMaxleft = sampleleft;  // save just the max levels
        }
        else if (sampleleft < signalMinleft)
        {
          signalMinleft = sampleleft;  // save just the min levels
        }
      }
    }
    peakToPeakleft = signalMaxleft - signalMinleft;  // max - min = peak-peak amplitude
    int levelleft = (peakToPeakleft * 54  / 1023);

    if (direction == FORWARD)
    {
      ledsleft[levelleft] = (levelleft - (NUM_LEDS / 2) - 1, levelleft, 0, CHSV(gHue, 240, 240));
    }
    else
    {
      ledsleft[levelleft] = (levelleft - (NUM_LEDS / 2) - 1, levelleft, 0, CHSV(gHue, 240, 240));
      ledsleft[NUM_LEDS - 1 - levelleft] = (levelleft - (NUM_LEDS / 2) - 1, levelleft, 0, CHSV(gHue, 240, 240));
    }


    //audio right-----------------------------------------------

    const int sampleWindowright = 12.5; // Sample window width in mS (50 mS = 20Hz)
    unsigned int sampleright;

    unsigned long startMillisright = millis(); // Start of sample window
    unsigned int peakToPeakright = 0;   // peak-to-peak level

    unsigned int signalMaxright = 0;
    unsigned int signalMinright = 1023;

    // collect data for sample window time (ms)
    while (millis() - startMillisright < sampleWindowright)
    {
      sampleright = analogRead(A0);
      if (sampleright < 1023)  // toss out spurious readings
      {
        if (sampleright > signalMaxright)
        {
          signalMaxright = sampleright;  // save just the max levels
        }
        else if (sampleright < signalMinright)
        {
          signalMinright = sampleright;  // save just the min levels
        }
      }
    }
    peakToPeakright = signalMaxright - signalMinright;  // max - min = peak-peak amplitude
    int levelright = (peakToPeakright * 54 / 1023);

    if (direction == FORWARD)
    {
      ledsright[levelright] = (levelright - (NUM_LEDS / 2) - 1, levelright, 0, CHSV(gHue, 240, 240));
    }
    else
    {
      ledsright[levelright] = (levelright - (NUM_LEDS / 2) - 1, levelright, 0, CHSV(gHue, 240, 240));
      ledsright[NUM_LEDS - 1 - levelright] = (levelright - (NUM_LEDS / 2) - 1, levelright, 0, CHSV(gHue, 240, 240));
    }
  }

  else if ( prog == 8) //lamp
  {
    for (int led = 0; led < NUM_LEDS; led++)
    {
      mappedHue = msgHue;
      ledsleft[led] = CHSV(mappedHue, 255, 255);
      ledsright[led] = CHSV(mappedHue, 255, 255);
    }
  }

  else if (prog == 9) //breathe
  {
    //breath colour
    for (int led = 0; led < NUM_LEDS; led++)
    {
      breathColour = msgHue;
      ledsleft[led] = CHSV(breathColour, 255, 255);
      ledsright[led] = CHSV(breathColour, 255, 255);
    }

    int BrightnessMaxVal = msgBrightness * 1.4;

    float breathlight = (exp(sin(millis() / 4000.0 * PI)) - 0.36787944) * 108.0;
    FastLED.setBrightness(constrain(breathlight, 0, BrightnessMaxVal));
    FastLED.show();
  }

  else if (prog == 10)  //fire
  {
    fireHue = msgHue;

    CRGB darkcolour  = CHSV(fireHue, 255, 192); // pure hue, three-quarters brightness
    CRGB lightcolour = CHSV((fireHue - 25), 128, 200); // half 'whitened', full brightness

    gPal = CRGBPalette16( CRGB::Black, darkcolour, lightcolour, CRGB::White);

    // Add entropy to random number generator
    random16_add_entropy( random());

    Fire2012WithPalette(); // run simulation using palette colors

    FastLED.show(); // display this frame
    FastLED.delay(1000 / FRAMES_PER_SECOND);
  }

  else if (prog == 11)//juggle
  {
    // Several colored dots, weaving in and out of sync with each other

    numdots = msgBallCount;                                                       // Number of dots in use.
    uint8_t hueinc = 60;                                                       // Incremental change in hue between each dot.
    uint8_t thishue = 0;                                                       // Starting hue.
    uint8_t curhue = msgHue;                                                           // The current hue
    uint8_t thissat = 255;                                                     // Saturation of the colour.
    uint8_t thisbright = 255;                                                    // How bright should the LED/display be.
    uint8_t basebeat = 10;                                                      // Higher = faster movement.

    for ( int i = 0; i < numdots; i++)
    {
      ledsleft[beatsin16(basebeat + i + numdots, 0, NUM_LEDS)] += CHSV(curhue, thissat, thisbright); //beat16 is a FastLED 3.1 function
      ledsright[beatsin16(basebeat + i + numdots, 0, NUM_LEDS)] += CHSV(curhue, thissat, thisbright); //beat16 is a FastLED 3.1 function
      curhue += hueinc;
    }
  }

  else if (prog == 12) // rainbow
  {
    speed = msgHue * 0.58824; //scales msgHue form 0-255 to 0-150
    fill_rainbow(ledsleft, NUM_LEDS, newHue, 7);
    fill_rainbow(ledsright, NUM_LEDS, newHue, 7);

    if (direction == FORWARD )
    {
      newHue += 5;
    }
    else
    {
      newHue -= 5;
    }
    delay(speed);
  }


  else if (prog == 13) //bpm -- work in progress
  { // coloured stripes pulsing at a (currently) defined bpm
    CRGBPalette16 palette = RainbowColors_p;
    newHue = msgHue;
    int sensitvity = msgSens;
    int beatValleft = analogRead(A1);
    int beatValright = analogRead(A1);

    /*add a buffer to sample the audio and determine the current bpm.

       possibly use buffer? sample window?

    */


    uint8_t BeatsPerMinute = msgBallCount; // 62; //needs to be to be adjustable in accoradance to current audio bpm
    uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);


    if (direction == FORWARD) {
      for ( int i = 0; i < NUM_LEDS; i++)
      { int testVar =  beat - newHue + (i * 10);

        ledsleft[i] = ColorFromPalette(palette, newHue + (i * 2), testVar);
        ledsright[i] = ColorFromPalette(palette, newHue + (i * 2), testVar);
      }
    }
    else
    {
      for ( int i = 0; i < NUM_LEDS; i++)
      {
        ledsleft[NUM_LEDS - 1 - i] = ColorFromPalette(palette, newHue + (i * 2), beat - newHue + (i * 10));
        ledsright[NUM_LEDS - 1 - i] = ColorFromPalette(palette, newHue + (i * 2), beat - newHue + (i * 10));
      }
    }
  }


  else if (prog == 14)//LED controlled by Mouse Position
  {
    newHue = msgHue;
    mappedHueleft = newHue;
    mappedHueright = newHue;
    x = msgX;
    y = msgY;

    int max_x = 1920 + 5; //allow values to over extend -- these values are for screen resolution 1920*1080
    int max_y = 1080 + 5;
    if (direction == FORWARD)
    {
      int numLedsToLightleft = map(x, 0, max_x, 0, NUM_LEDS);
      int numLedsToLightright = map(y, 0,  max_y, 0, NUM_LEDS);

      ledsleft[numLedsToLightleft] = CHSV((newHue + (2 * numLedsToLightleft)), 255, 255);
      ledsright[NUM_LEDS - 1 - numLedsToLightright] = CHSV((newHue + (2 * numLedsToLightright)), 255, 255);
    }
    else
    {
      int numLedsToLightleft = map(x, 0, max_x, 0, NUM_LEDS + 1);
      int numLedsToLightright = map(y, 0,  max_y, 0, NUM_LEDS + 1);

      for (int led = 0; led < numLedsToLightleft; led++)
      {
        ledsleft[led] = CHSV(mappedHueleft, 255, 255);
        mappedHueleft += 5;
      }
      for (int led = 0; led < numLedsToLightright; led++)
      {
        ledsright[NUM_LEDS - 1 - led] = CHSV(mappedHueright, 255, 255);
        mappedHueright += 5;
      }

    }
  }

  else if (prog == 15)
  {  }


  FastLED.show();                     //leave at end of 'program'
} //program()


//--------------------------------------------------------




void Fire2012WithPalette()
{
  // Array of temperature readings at each simulation cell
  static byte heatleft[NUM_LEDS];
  static byte heatright[NUM_LEDS];

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < NUM_LEDS; i++)
  {
    heatleft[i] = qsub8( heatleft[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    heatright[i] = qsub8( heatright[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = NUM_LEDS - 1; k >= 2; k--)
  {
    heatleft[k] = (heatleft[k - 1] + heatleft[k - 2] + heatleft[k - 2] ) / 3;
    heatright[k] = (heatright[k - 1] + heatright[k - 2] + heatright[k - 2] ) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if ( random8() < SPARKING )
  {
    int y = random8(7);
    heatleft[y] = qadd8( heatleft[y], random8(160, 255) );
    heatright[y] = qadd8( heatright[y], random8(160, 255) );
  }

  // Step 4.  Map from heat cells to LED colors
  for ( int j = 0; j < NUM_LEDS; j++)
  {
    // Scale the heat value from 0-255 down to 0-240
    // for best results with colour palettes.
    byte colourindexleft = scale8( heatleft[j], 240);
    byte colourindexright = scale8( heatright[j], 240);

    CRGB colourleft = ColorFromPalette( gPal, colourindexleft);
    CRGB colourright = ColorFromPalette( gPal, colourindexright);

    int pixelnumberleft, pixelnumberright;

    if ( direction == !FORWARD )
    {
      pixelnumberleft = (NUM_LEDS - 1) - j;
      pixelnumberright = (NUM_LEDS - 1) - j;
    }
    else
    {
      pixelnumberleft = j;
      pixelnumberright = j;
    }
    ledsleft[pixelnumberleft] = colourleft;
    ledsright[pixelnumberright] = colourright;
  }
}

void addGlitter( fract8 chanceOfGlitter)
{
  if ( random8() < chanceOfGlitter)
  {
    ledsleft[ random16(NUM_LEDS) ] += CRGB::White;
    ledsright[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

