#include <Charliplexing.h>
#include <avr/pgmspace.h>

int8_t x1, y1;
int xpot = A0;
int xpotval = 0;

void setup()
{
  LedSign::Init(DOUBLE_BUFFER);
  x1 = 0;
  y1 = 0;

}

void loop()
{
  xpotval = analogRead(xpot);
  LedSign::Clear();
  x1 = map(xpotval, 0, 50, 0, 13);
  y1 = map(xpotval, 0, 50, 0, 8);

  LedSign::Set(x1, y1, 1);
  LedSign::Flip();
  delay(30);
}
