#include "LedControl.h"
#define SCREEN_X 8
#define SCREEN_Y 16
LedControl lc = LedControl(11, 13, 10, 4); // CLK, DIN, CS, Number of LED Module
const unsigned long delaytime = 300;       // time to updates of the display
#define D0 1
#define D1 0

// Pong Variable
int x = 3;
int y = 7;
int dx;
int dy = 1;
int bat;
byte sad[] =
{
  B00000000,
  B00000000,
  B00000100,
  B00000000,
  B00000011,
  B00000000,
  B00000100,
  B00000000
};
byte sad2[] =
{
  B00000000,
  B00000000,
  B00100000,
  B01000000,
  B01000000,
  B01000000,
  B00100000,
  B00000000
};
void setSprite(byte *sprite)
{
  for (int r = 0; r < 8; r++)
  {
    lc.setRow(D0, r, sprite[r]);
  }
}
void setSprite2(byte *sprite)
{
  for (int r = 0; r < 8; r++)
  {
    lc.setRow(D1, r, sprite[r]);
  }
}
void setup()
{
  randomSeed(analogRead(A1));
  int devices = lc.getDeviceCount(); // find no of LED modules
  //we have to init all devices in a loop
  for (int address = 0; address < devices; address++)
  { // set up each device
    lc.shutdown(address, false);
    lc.setIntensity(address, 8);
    lc.clearDisplay(address);
  }

  bat = map(analogRead(A0), 0, 1023, 0, 7);
  // first pong bat drawing
  lc.setLed(D0, bat - 1, 0, true);
  lc.setLed(D0, bat, 0, true);
  lc.setLed(D0, bat + 1, 0, true);
  // second pong bat
  lc.setLed(D1, bat - 1, 7, true);
  lc.setLed(D1, bat, 7, true);
  lc.setLed(D1, bat + 1, 7, true);
  // show pong
  lc.setLed(y / 8, x, y % 8, true);
  delay(delaytime);
}

void loop()
{
  lc.clearDisplay(0);
  lc.clearDisplay(1);

  bat = map(analogRead(A0), 0, 1023, 0, 7);
  // first pong bat drawing
  lc.setLed(D0, bat - 1, 0, true);
  lc.setLed(D0, bat, 0, true);
  lc.setLed(D0, bat + 1, 0, true);
  // second pong bat
  lc.setLed(D1, bat - 1, 7, true);
  lc.setLed(D1, bat, 7, true);
  lc.setLed(D1, bat + 1, 7, true);
  // move pong
  x += dx;
  y += dy;
  hitPong();
  hitWall();
  if (0 <= y && y < SCREEN_Y)
  {
    int address = (y / 8 == 0) ? D0 : D1;
    lc.setLed(address, x, y % 8, true);
  }
  else
  {
    tone(3,261);
    delay(100);
    noTone(3);
    setSprite(sad);
    setSprite2(sad2);
    //lc.clearDisplay(0);
    delay(3000);
    x = 3;
    y = 7;
  }

  delay(delaytime);
}

void hitPong()
{
  if (bat - 1 <= x && x <= bat + 1)
  {
    if (y == 1) // Hit top
    {
      tone(3,392);
      dx = random(-1, 2);
      dy = 1;
      delay(100);
      noTone(3);
    }
    else if (y == 14) // Hit bottom
    {
      tone(3,392);
      dx = random(-1, 2);
      dy = -1;
      delay(100);
      noTone(3);
    }
  }
}

void hitWall()
{
  if (x == 0 && dx != 0) // Hit left
  {
    tone(3,392);
    delay(100);
    noTone(3);
    dx = 1;
  }
  else if (x == 7 && dx != 0) // Hit right
  {
    tone(3,392);
    delay(100);
    noTone(3);
    dx = -1;
  }
}