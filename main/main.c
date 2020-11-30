/* Created 19 Nov 2016 by Chris Osborn <fozztexx@fozztexx.com>
 * http://insentricity.com
 *
 * Demo of driving WS2812 RGB LEDs using the RMT peripheral.
 *
 * This code is placed in the public domain (or CC0 licensed, at your option).
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <soc/rmt_struct.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <stdio.h>
#include "ws2812.h"
#include "ledstrip_effect.h"

#include "esp_log.h"

static const char *TAG = "main";


#define WS2812_PIN 15
#define LED_COUNT 150 // Number of your "pixels"

rgbVal *pixels;

#define delay_ms(ms) vTaskDelay((ms) / portTICK_RATE_MS)

void random_effects(void *pvParameters){
  while (1) {
    ESP_LOGI(TAG, "cylonBounce");
    cylonBounce(pixels, LED_COUNT, 0xff, 0, 0, 4, 10, 50);
    ESP_LOGI(TAG, "colorWipe");
    colorWipe(pixels, LED_COUNT, 0xff, 0x00, 0x00, 50);
    colorWipe(pixels, LED_COUNT, 0x00, 0x00, 0x00, 50);
    ESP_LOGI(TAG, "meteorRain");
    meteorRain(pixels, LED_COUNT, 0xff, 0x40, 0x00, 5, 64, true, 10);
    ESP_LOGI(TAG, "rainbowCycle");
    rainbowCycle(pixels, LED_COUNT, 10);
    ESP_LOGI(TAG, "RGBLoop");
    RGBLoop(pixels, LED_COUNT, 5);
    /*if (count == 0) {
        red = 0x00;
        green = 0xff;
        count = 1;
      } else if (count == 1)
      {
        blue = 0xff;
        green = 0x00;
        count = 2;
      } else {
        red = 0xff;
        blue = 0x00;
        count = 0;
      }*/
  }
}

void app_main()
{
  nvs_flash_init();
  ws2812_init(WS2812_PIN);
  pixels = malloc(sizeof(rgbVal) * LED_COUNT);
  //xTaskCreate(rainbow, "ws2812 rainbow", 4096, NULL, 10, NULL);
  //xTaskCreate(cylon_bounce, "ws2812 cylon_bounce", 4096, NULL, 10, NULL);
  //xTaskCreate(color_wipe, "ws2812 color_wipe", 4096, NULL, 10, NULL);
  xTaskCreate(random_effects, "ws2812 random_effects", 4096, NULL, 10, NULL);
  
  return;
}
