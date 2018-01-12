#include <Charliplexing.h>
#include <avr/pgmspace.h>

int8_t x1, y1, dx1, dy1;
int8_t x2, y2, dx2, dy2;

void setup() {
  LedSign::Init(DOUBLE_BUFFER);

  x1 = 3;
  y1 = 7;
  dx1 = 1;
  dy1 = 1;

  x2 = 11;
  y2 = 2;
  dx2 = 1;
  dy2 = 1;

}

void loop() {
  int8_t randommove;


  // The Balls shall bounce on the walls :
  if (x1 == 13 || x1 == 0) dx1 = -dx1;
  if (y1 == 8 || y1 == 0) dy1 = -dy1;

  if (x2 == 13 || x2 == 0) dx2 = -dx2;
  if (y2 == 8 || y2 == 0) dy2 = -dy2;


  // Clear the non-active screen
  LedSign::Clear();

  // Move the BALLs :
  x1 = x1 + dx1;
  y1 = y1 + dy1;

  x2 = x2 + dx2;
  y2 = y2 + dy2;

  // Draw the balls :
  LedSign::Set(x1, y1, 1);
  LedSign::Set(x2, y2, 1);
  LedSign::Flip();

  // Display the bitmap some times
  delay(100);

  // loop :)

}
