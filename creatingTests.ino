#include <Arduino_FreeRTOS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
#define BLACK       0x0000
#define WHITE       0xFFFF
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
void TaskBlink1( void *pvParameters );
void TaskBlink2( void *pvParameters );
void Taskprint( void *pvParameters );
void setup() {
  // initialize serial communication at 9600 bits per second:
#ifdef USE_ADAFRUIT_SHIELD_PINOUT
#else
#endif
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  Serial.begin(9600);
  xTaskCreate(TaskBlink1, "Task1", 128, NULL, 1, NULL);
  xTaskCreate(TaskBlink2, "Task2 ", 128, NULL, 1, NULL);
  xTaskCreate(Taskprint, "Task3", 128, NULL, 0, NULL);
  vTaskStartScheduler();
}
void loop()
{
}
void TaskBlink1(void *pvParameters)  {
  while (1)
  {
    Serial.println("Task1");
    tft.fillScreen(BLACK);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
  }
}
void TaskBlink2(void *pvParameters)
{
  while (1)
  {
    Serial.println("Task2");
    tft.fillScreen(WHITE);
    vTaskDelay( 3000 / portTICK_PERIOD_MS );
  }
}
void Taskprint(void *pvParameters)  {
  int counter = 0;
  while (1)
  {
    counter++;
    Serial.println(counter);
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}
