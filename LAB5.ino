#define LED_W_R 7
#define LED_W_Y 6
#define LED_W_G 5
#define BUTTON_W 2

#define LED_S_R 10
#define LED_S_Y 9
#define LED_S_G 8
#define BUTTON_S 3

#define LED_P_R 11
#define LED_P_G 12
#define BUTTON_P 4

#define goW 0
#define waitWS 1
#define waitWP 2
#define goS 3
#define waitSW 4
#define waitSP 5
#define goP 6
#define blink_1W 7
#define blink_2W 8
#define blink_3W 9
#define blink_4W 10
#define blink_5W 11
#define blink_6W 12
#define blink_1S 13
#define blink_2S 14
#define blink_3S 15
#define blink_4S 16
#define blink_5S 17
#define blink_6S 18
unsigned long s = 0;
struct state
{
  unsigned long st_out;
  unsigned long time;
  unsigned long st_next[8];
};
typedef struct state Stype;
Stype FSM[19]=
{
  {B01001100,2000,{goW,goW,waitWS,waitWS,waitWP,waitWP,waitWS,waitWS}}, //goW 0
  {B01001010,500,{goS,goS,goS,goS,goS,goS,goS,goS}}, //waitWS -> gos
  {B01001010,500,{goP,goP,goP,goP,goP,goP,goP,goP}}, //waitWP - > goS
  {B01100001,2000,{goS,waitSW,goS,waitSW,waitSP,waitSP,waitSP,waitSP}}, //goS 
  {B01010001,500,{goW,goW,goW,goW,goW,goW,goW,goW}}, //waitSW -> goW
  {B01010001,500,{goP,goP,goP,goP,goP,goP,goP,goP}}, //waitSP -> goP
  {B10001001,2000,{goP,blink_1W,blink_1S,blink_1S,goP,blink_1W,blink_1S,blink_1W}}, //goP
  {B00001001,500,{blink_2W,blink_2W,blink_2W,blink_2W,blink_2W,blink_2W,blink_2W,blink_2W}}, //bilnk_1W
  {B10001001,500,{blink_3W,blink_3W,blink_3W,blink_3W,blink_3W,blink_3W,blink_3W,blink_3W}}, //bilnk_2W
  {B00001001,500,{blink_4W,blink_4W,blink_4W,blink_4W,blink_4W,blink_4W,blink_4W,blink_4W}}, //bilnk_3W
  {B10001001,500,{blink_5W,blink_5W,blink_5W,blink_5W,blink_5W,blink_5W,blink_5W,blink_5W}}, //bilnk_4W
  {B00001001,500,{blink_6W,blink_6W,blink_6W,blink_6W,blink_6W,blink_6W,blink_6W,blink_6W}}, //bilnk_5W
  {B10001001,500,{goW,goW,goW,goW,goW,goW,goW,goW}}, //bilnk_6W
  {B00001001,500,{blink_2S,blink_2S,blink_2S,blink_2S,blink_2S,blink_2S,blink_2S,blink_2S}}, //bilnk_1S
  {B10001001,500,{blink_3S,blink_3S,blink_3S,blink_3S,blink_3S,blink_3S,blink_3S,blink_3S}}, //bilnk_2S
  {B00001001,500,{blink_4S,blink_4S,blink_4S,blink_4S,blink_4S,blink_4S,blink_4S,blink_4S}}, //bilnk_3S
  {B10001001,500,{blink_5S,blink_5S,blink_5S,blink_5S,blink_5S,blink_5S,blink_5S,blink_5S}}, //bilnk_4S
  {B00001001,500,{blink_6S,blink_6S,blink_6S,blink_6S,blink_6S,blink_6S,blink_6S,blink_6S}}, //bilnk_5S
  {B10001001,500,{goS,goS,goS,goS,goS,goS,goS,goS}}, //bilnk_6S
};
void setup()
{
  pinMode(LED_W_R, OUTPUT);
  pinMode(LED_W_Y, OUTPUT);
  pinMode(LED_W_G, OUTPUT);
  pinMode(BUTTON_W, INPUT);
  
  pinMode(LED_S_R, OUTPUT);
  pinMode(LED_S_Y, OUTPUT);
  pinMode(LED_S_G, OUTPUT);
  pinMode(BUTTON_S, INPUT);
  
  pinMode(LED_P_R, OUTPUT);
  pinMode(LED_P_G, OUTPUT);
  pinMode(BUTTON_P, INPUT);
  
  Serial.begin(9600);
}

int input,input1,input2,input3;
void loop()
{
  digitalWrite(LED_W_R, FSM[s].st_out& B00000001);
  digitalWrite(LED_W_Y, FSM[s].st_out& B00000010);
  digitalWrite(LED_W_G, FSM[s].st_out& B00000100);
  
  digitalWrite(LED_S_R, FSM[s].st_out& B00001000);
  digitalWrite(LED_S_Y, FSM[s].st_out& B00010000);
  digitalWrite(LED_S_G, FSM[s].st_out& B00100000);
  
  digitalWrite(LED_P_R, FSM[s].st_out& B01000000);
  digitalWrite(LED_P_G, FSM[s].st_out& B10000000);
  
  delay(FSM[s].time);
  
  input1 = digitalRead(BUTTON_W);
  input2 = digitalRead(BUTTON_S);
  input3 = digitalRead(BUTTON_P);
  
  input = (input3*2+input2)*2 + input1;
  Serial.print(input);
  Serial.print(" ");
  Serial.println(s);
  s = FSM[s].st_next[input];
  
}
