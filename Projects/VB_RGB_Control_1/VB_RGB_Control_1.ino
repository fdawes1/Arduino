#include <stdlib.h>

int redPin = 9;
int greenPin = 10;
int bluePin = 11;


String src_msg = "";


void setup() {
  Serial.begin(9600);


  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}

void loop()
{

}

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

      analogWrite(redPin, getLEDValue(src_msg, 'R', 'G'));
      Serial.println(getLEDValue(src_msg, 'R', 'G'));
      analogWrite(greenPin, getLEDValue(src_msg, 'G', 'B'));
      Serial.println(getLEDValue(src_msg, 'G', 'B'));
      analogWrite(bluePin, getLEDValue(src_msg, 'B', 'E'));
      Serial.println(getLEDValue(src_msg, 'B', 'E'));

      src_msg = ""; //clear string awaiting next command


    }
  }
}

int getLEDValue(String src_msg, char c1, char c2)
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

