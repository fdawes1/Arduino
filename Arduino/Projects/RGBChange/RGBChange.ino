
int Rpot = A0;
int Gpot = A1;
int Bpot = A2;

int Rval, Gval, Bval = 0;

const int red = 11;
const int green = 10;
const int blue = 9;

int Redval, Greenval, Blueval;

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  Serial.begin(9600);
}
void loop()
{
  Rval = analogRead(Rpot);
  Gval = analogRead(Gpot);
  Bval = analogRead(Bpot);

  Redval = map(Rval, 0, 1023, 0, 20);
  Greenval = map(Gval, 0, 1023, 0, 20);
  Blueval = map(Bval, 0, 1023, 0, 20);

  analogWrite(red, Redval);
  analogWrite(green, Greenval);
  analogWrite(blue, Blueval);
}
