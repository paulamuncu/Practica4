#include <Arduino.h>
#define  LED  13
SemaphoreHandle_t xBinarySemaphore;

void LedoffTask(void *pvParameters);
void LedOnTask(void *pvParameters);

void setup(){
  Serial.begin(115200);
  pinMode(LED ,OUTPUT);
  xBinarySemaphore = xSemaphoreCreateBinary();
  xTaskCreate(LedOnTask, "LedON",10000,NULL,1,NULL);
  xTaskCreate(LedoffTask, "LedOFF", 10000,NULL,1,NULL);
  xSemaphoreGive(xBinarySemaphore);
}

void loop(){delay(1000);}
void LedOnTask(void *pvParameters)
{
  while(1)
  {
   xSemaphoreTake(xBinarySemaphore,portMAX_DELAY);
   Serial.println("Inside LedOnTask");
   digitalWrite(LED,LOW);
   delay(1000);
   xSemaphoreGive(xBinarySemaphore);
   vTaskDelay(1000);
  }
}
void LedoffTask(void *pvParameters)
{
  while(1)
  {
    xSemaphoreTake(xBinarySemaphore,portMAX_DELAY);
    Serial.println("Inside LedOffTask");
    digitalWrite(LED,HIGH);
    delay(1000);
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1000);
  }
}