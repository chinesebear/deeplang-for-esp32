/* UART Echo Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#ifdef CONFIG_IDF_TARGET_ESP32
#define CHIP_NAME "ESP32"
#endif

#ifdef CONFIG_IDF_TARGET_ESP32S2BETA
#define CHIP_NAME "ESP32-S2 Beta"
#endif
static int count = 0;
static void parser_task(void *arg)
{
    while (1) {
        printf("Deep parser run %d seconds...\n", count++);
        vTaskDelay(100);
    }
}

static void wasm_vm_task(void *arg)
{
    while (1) {
        printf("Deep wasm vm run %d seconds...\n", count++);
        vTaskDelay(100);
    }
}

static void event_manager_task(void *arg)
{
    while (1) {
        printf("Event manager run %d seconds...\n", count++);
        vTaskDelay(100);
    }
}

static void uart_file_manager_task(void *arg)
{
    while (1) {
        printf("Uart file manager run %d seconds...\n", count++);
        vTaskDelay(100);
    }
}

void app_main(void)
{

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU cores, WiFi%s%s, ",
            CHIP_NAME,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
    printf("silicon revision %d, ", chip_info.revision);
    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    printf ("There are %d ms per tick\r\n",portTICK_PERIOD_MS);
    /* Deepvm start */
    printf ("Deepvm for deeplang 1.0\r\n");
    printf ("Deepvm includes parser, wasm vm, event manager, uart file manager\r\n");
    xTaskCreate(parser_task, "parser_task", 2048, NULL, 10, NULL);
    xTaskCreate(wasm_vm_task, "wasm_vm_task", 2048, NULL, 10, NULL);
    xTaskCreate(event_manager_task, "event_manager_task", 2048, NULL, 12, NULL);
    xTaskCreate(uart_file_manager_task, "uart_file_manager_task", 2048, NULL, 12, NULL);
}
