#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define RED     8
#define GREEN   10
#define YELLOW  9
#define SW1     5
#define SW2     6
#define SW3     7

QueueHandle_t BlinkQueue;

void setup()
{
  Serial.begin(9600);
  BlinkQueue =  xQueueCreate(10, sizeof(int32_t));

  xTaskCreate(vSenderTask, "Sender Task 1", 100, SW1, 1, NULL);
  xTaskCreate(vSenderTask, "Sender Task 2", 100, SW2, 1, NULL);
  xTaskCreate(vSenderTask, "Sender Task 3", 100, SW3, 1, NULL);
  xTaskCreate(vReceiverTask, "Receiver Task", 100, NULL, 1, NULL);
}

void vSenderTask(void *pvParameters)
{
  BaseType_t qStatus;
  int32_t valueToSend = 0;
  int SW = (int32_t)pvParameters;
  pinMode(SW, INPUT);
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  while (1)
  {
    if (digitalRead(SW) == HIGH)
      valueToSend = SW;
    else
      valueToSend = 0;

    if (valueToSend != 0)
    {
      qStatus = xQueueSend(BlinkQueue, &valueToSend, 0);
      vTaskDelay(10);
    }
  }
}

void vReceiverTask(void *pvParameters)
{
  int32_t valueReceived;
  BaseType_t qStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
  long Time;
  int redOn = 0;
  int yellowOn = 0;
  int greenOn = 0;
  long redPress;
  long yellowPress;
  long greenPress;
  int redDuration = 0;
  int yellowDuration = 0;
  int greenDuration = 0;
  int count = 0;
  while (1)
  {
    Time = millis();
    qStatus = xQueueReceive(BlinkQueue, &valueReceived, xTicksToWait);
    if (qStatus == pdPASS)
    {
      vTaskDelay(10);
      Serial.println(valueReceived);

      if (valueReceived == SW1 && redOn == 0)
      {
        redPress = Time;
        redOn = 1;
        count++;
        redDuration = 3000;
        digitalWrite(RED, HIGH);
      }
      else if (valueReceived == SW1)
      {
        redDuration += 3000;
      }
      else if (valueReceived == SW2)
      {
        yellowPress = Time;
        yellowOn = !yellowOn;
        digitalWrite(YELLOW, HIGH);
      }
      else if (valueReceived == SW3 &&  greenOn == 0)
      {
        greenOn = 1;
        greenPress = Time;
        greenDuration = 500;
      }
    }
    if (Time - redPress > redDuration)
    {
      redOn = 0;
      redDuration = 0;
      digitalWrite(RED, LOW);
    }
    if (yellowOn && Time - yellowPress > 1000)
    {
      digitalWrite(YELLOW, HIGH);
      yellowPress = Time;
    }
    else if (yellowOn && Time - yellowPress > 500)
    {
      digitalWrite(YELLOW, LOW);
    }
    else if (yellowOn == 0)
    {
      digitalWrite(YELLOW, LOW);
    }
    if (Time - greenPress > greenDuration && greenOn == 1)
    {
      digitalWrite(GREEN, !digitalRead(GREEN));
      greenDuration += 500;
    }
    if (greenDuration >= 3500 && greenOn == 1)
    {
      greenOn = 0;
      digitalWrite(GREEN, LOW);
      greenDuration += 500;
    }
  }
}
void loop() {}