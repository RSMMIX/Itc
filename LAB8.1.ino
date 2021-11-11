#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define RED     8
#define YELLOW  9
#define GREEN   10
#define SW1     5
#define SW2     6
#define SW3     7

QueueHandle_t BlinkQueue;

void setup()
{
  BlinkQueue =  xQueueCreate(10, sizeof(int32_t));
  xTaskCreate(vSenderTask, "Sender Task 1", 100, SW1, 1, NULL);
  xTaskCreate(vSenderTask, "Sender Task 1", 100, SW2, 1, NULL);
  xTaskCreate(vSenderTask, "Sender Task 1", 100, SW3, 1, NULL);
  xTaskCreate(vReceiverTask, "Receiver Task ", 100, RED, 1, NULL);
  xTaskCreate(vReceiverTask, "Receiver Task", 100, YELLOW, 1, NULL);
  xTaskCreate(vReceiverTask, "Receiver Task", 100, GREEN, 1, NULL);
}

void vSenderTask(void *pvParameters)
{
  BaseType_t qStatus;
  int32_t valueToSend = 0;
  int SW = (int32_t)pvParameters;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  pinMode(SW, INPUT);
  while (1)
  {
    if (digitalRead(SW) == HIGH)
      valueToSend = SW;
    else
      valueToSend = 0;

    if (valueToSend )
    {
      qStatus = xQueueSend(BlinkQueue, &valueToSend, xTicksToWait);
      vTaskDelay(10);
    }
  }
}

void vReceiverTask(void *pvParameters)
{
  int LED = (int32_t)pvParameters;
  int32_t valueReceived;
  BaseType_t qStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  pinMode(RED, OUTPUT); digitalWrite(RED, LOW);
  pinMode(YELLOW, OUTPUT); digitalWrite(YELLOW, LOW);
  pinMode(GREEN, OUTPUT); digitalWrite(GREEN, LOW);
  bool YELLOW_status = false;
  while (1)
  {
    qStatus = xQueueReceive(BlinkQueue, &valueReceived, xTicksToWait);
    if (qStatus  == pdPASS)
    {
      Serial.println(valueReceived);
      if (valueReceived == 5 && LED == RED)
      {
        digitalWrite(RED, 1);
        vTaskDelay(150);
        digitalWrite(RED, 0);
      }
      else if (valueReceived == 6 && LED == YELLOW)
      {
        YELLOW_status = !YELLOW_status;
      }
      else if (valueReceived == 7 && LED == GREEN)
      {
        digitalWrite(GREEN, 1);
        vTaskDelay(50);
        digitalWrite(GREEN, 0);
        vTaskDelay(50);
        digitalWrite(GREEN, 1);
        vTaskDelay(50);
        digitalWrite(GREEN, 0);
        vTaskDelay(50);
        digitalWrite(GREEN, 1);
        vTaskDelay(50);
        digitalWrite(GREEN, 0);
        vTaskDelay(50);
      }
      else if (valueReceived != 7)
      {
        int32_t valueReceived = valueReceived;
        xQueueReceive(BlinkQueue, &valueReceived, xTaskCreate);
        vTaskDelay(1);
      }
    }
    if (YELLOW_status && LED == YELLOW)
    {
      digitalWrite(YELLOW, HIGH);
      vTaskDelay(20);
      digitalWrite(YELLOW, LOW);
      vTaskDelay(20);
    }
  }
}
void loop() {}