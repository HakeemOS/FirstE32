#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "driver/gpio.h"



#if CONFIG_FREERTOS_UNICORE                                                             //set app_cpu to single core
static const BaseType_t app_cpu = 0; 
#else 
static const BaseType_t app_cpu = 1; 
#endif

#define led_pin 13                                                                      // Onboard led

void blinkFunc(void* parameter){
    while(1){

        gpio_set_level(led_pin, 1); 
        vTaskDelay(2000/portTICK_PERIOD_MS);                                            //Period = 4s; Duty cycle = 50%
        gpio_set_level(led_pin, 0); 
        vTaskDelay(2000/portTICK_PERIOD_MS); 
    };
 }

void setup(){
    char* ourTaskName = pcTaskGetName(NULL);                                        
    ESP_LOGI(ourTaskName, "Hello, starting up ... \n");                                 //Log message with task name
    gpio_reset_pin(led_pin); 
    gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);                                   
    xTaskCreatePinnedToCore(blinkFunc, "Blinky", 1024, NULL, 1, NULL, app_cpu );        //Ensure single core use during task
} 

void app_main(void){
    setup(); 

}