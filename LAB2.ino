int button1 = 3;
int button2 = 4;
int button3 = 2;
void setup()
{
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(button3,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600);
  attachInterrupt(1, RedSwitch, FALLING);
  attachInterrupt(0, GreenSwitch, FALLING);
}
void loop()
{
  if(digitalRead(button1) == LOW)
  {
    digitalWrite(13, HIGH);
    delay(3000);
    digitalWrite(13,LOW);
  }
  if(digitalRead(button3) == LOW)
  {
    digitalWrite(11, HIGH);
    delay(3000);
    digitalWrite(11,LOW);
  }
  if(digitalRead(button2) == LOW)
  {
    digitalWrite(12, HIGH);
    delay(500);
    digitalWrite(12,LOW);
    delay(500);
    digitalWrite(12, HIGH);
    delay(500);
    digitalWrite(12,LOW);
    delay(500);
  }
}
void RedSwitch()
{
  digitalWrite(13,!digitalRead(13));
}
void GreenSwitch()
{
  if(digitalRead(13) == LOW)
  {
    digitalWrite(11,!digitalRead(11));
  }
}