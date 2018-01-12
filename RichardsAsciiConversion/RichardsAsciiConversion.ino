#define switchPin 2 // switch input
#define motor1Pin 3 // Motor 1 leg 1 (pin 2, 1A)
#define motor2Pin 4 // Motor 1 leg 2 (pin 7, 2A)
#define motor3Pin 6 // Motor 2 leg 1
#define motor4Pin 7 // Motor 2 leg 2
#define enable1Pin 9 // Motor1 enable pin
#define enable2Pin 10 // Motor2 enable pin
#define ledPin 13 // Reset LED
#define slack 50 // Slack in joystick
int Y_axis_initial = 0; // Defines starting position of Y axis
char stickRead[5]; // Defines character size of 4 for reading serial input, 5th is null
int stickY; // Stick value
void setup()
{
  Serial.begin(9600);   //Turn on the Serial Port at 9600 bps
 
  // Sets scaling factors and reads initial value at program start
  int x;  // Sets storage variable for Serial.read()
  int i = 0; // Defines a counter for while loop
  Serial.flush();
  while(((x = Serial.read()) != 13) && ( x != 10 ));
  while( Y_axis_initial == 0 )
  {
    while(((x = Serial.read()) != 13) && ( x != 10 ))
    {
      if( x != -1)
      {
        stickRead[i++] = x;
      }
      stickRead[i] = '\0';
    }
    Y_axis_initial = atoi(stickRead);
  }
 
  // set the switches as an input:
  pinMode(switchPin, INPUT);
  // set all the other pins you're using as outputs:
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(motor3Pin, OUTPUT);
  pinMode(motor4Pin, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  pinMode(ledPin, OUTPUT);
 
  // blink the LED 3 times. This should happen only once.
  // if you see the LED blink three times, it means that the module
  // reset itself,. probably because the motor caused a brownout
  // or a short.
  blink(ledPin, 3, 100);
}
void loop()
{
  // Reads position of A0 and A1 (X and Y axis)
  int x;  // Sets storage variable for Serial.read()
  int i = 0;  // Defines a counter for while loop
  while( ( ( x = Serial.read() ) != 13 ) && ( x != 10 ) )
  {
    if( x != -1 )
    {
      stickRead[i++] = x;
    }
   
  }
  stickRead[i]='\0';
  int oldstick = stickY;
  stickY = atoi(stickRead);
  if( stickY == 0 )
  {
    stickY = oldstick;
  }
 
  int minus_Y = abs(stickY-510)/2;
  int plus_Y = abs(stickY-513)/2;
  // Reads the position of Y axis and determines direction and speed
  if (stickY < Y_axis_initial-slack)
  {
    analogWrite(enable2Pin, minus_Y);
    digitalWrite(motor3Pin, HIGH); // set leg 1 of the Motor2 high
    digitalWrite(motor4Pin, LOW); // set leg 2 of the Motor2 low
    analogWrite(enable1Pin, minus_Y);
    digitalWrite(motor1Pin, HIGH); // set leg 1 of the Motor1 high
    digitalWrite(motor2Pin, LOW); // set leg 2 of the Motor1 low
  }
  if (abs(stickY - Y_axis_initial) < slack)  // Sets deadspace on stick
  {
    digitalWrite(enable2Pin, LOW);
    digitalWrite(enable1Pin, LOW);
  }
  if (stickY > Y_axis_initial+slack)
  {
    analogWrite(enable2Pin, plus_Y);
    digitalWrite(motor3Pin, LOW); // set leg 1 of the Motor2 low
    digitalWrite(motor4Pin, HIGH); // set leg 2 of the Motor2 low
    analogWrite(enable1Pin, plus_Y);
    digitalWrite(motor1Pin, LOW); // set leg 1 of the Motor1 low
    digitalWrite(motor2Pin, HIGH); // set leg 2 of the Motor1 high
  }
}
//blinks an LED
void blink(int whatPin, int howManyTimes, int milliSecs)
{
  int i = 0;
  for ( i = 0; i < howManyTimes; i++)
  {
    digitalWrite(whatPin, HIGH);
    delay(milliSecs/2);
    digitalWrite(whatPin, LOW);
    delay(milliSecs/2);
  }
}
