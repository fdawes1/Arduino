#include <Servo.h>

String src_msg;

#define led1  12
#define led2  11

Servo myServo;

int pos = 0;

int msgVal = 0;
int wristRoll;
float WRoll;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(8);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int wristRoll = int(WRoll);
  myServo.write(round(wristRoll));
  delay (100);
}


//----------------------------------- Visual Studio Code ----------------------------------------------------------------------------------------------------------------------
//
//
void serialEvent()
{
  if (Serial.available())
  {
    char inChar = (char) Serial.read();
    if (inChar != 'E')
    {
      src_msg += inChar;
    }


    if (inChar == 'E')
    {
      src_msg += inChar;

      WRoll = getSrcValue (src_msg, 'W', 'P');
      msgVal = getSrcValue (src_msg, 'P', 'E');

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
