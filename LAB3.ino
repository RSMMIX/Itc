#define Pressed 0
int nownumber = 0;
int bitPattern[13] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xc2, 0xc7, 0xff};
const int segmentPins[8] = {2,3,4,5,6,7,8};
int count = 1;
int randnum;
unsigned long int s11 = 0, s12 = 0;
void segment(int i)
{
  boolean setbit;
  for(int j=0;j<7;j++)
      {
          setbit = bitRead(bitPattern[i],j);
          digitalWrite(segmentPins[j],setbit);
      }
}
void setup() 
{
  randomSeed(analogRead(A0));
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  Serial.begin(9600);
  for(int i = 0; i < 8;i++)
  {
    pinMode(segmentPins[i], OUTPUT);
  }
  for(int j=0;j<7;j++)
  {
    digitalWrite(segmentPins[j],1);
  }
  randnum = random(1,10);
}
void loop() 
{
  Serial.println(randnum);
  if(millis() - s11 > 200 && digitalRead(11) == Pressed)
  {
    segment(count);
    nownumber = count;
    count++;
    if(count > 9){count = 1;}
    s11 = millis();
  }
  if(millis()- s12 > 200 && digitalRead(12) == Pressed)
  {
    if(nownumber == randnum)
    {
      segment(0);
      delay(300);
      segment(12);
      delay(300);
      segment(0);
      delay(300);
      segment(12);
      delay(300);
      segment(0);
      delay(300);
      segment(nownumber);
      count = nownumber;
      randnum = random(1,10);
    }
    else if(nownumber > randnum)
    {
      segment(10);
      delay(300);
      segment(12);
      delay(300);
      segment(10);
      delay(300);
      segment(12);
      delay(300);
      segment(10);
      delay(300);
      segment(nownumber);
      count = nownumber;
    }
    else if(nownumber < randnum)
    {
      segment(11);
      delay(300);
      segment(12);
      delay(300);
      segment(11);
      delay(300);
      segment(12);
      delay(300);
      segment(11);
      delay(300);
      segment(nownumber);
      count = nownumber;
    }
    s12 = millis();
  }
}