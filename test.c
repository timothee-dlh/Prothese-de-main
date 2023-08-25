#include "stdio.h"
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include "driver/ledc.h"
#include "hal/ledc_types.h"

void taskCodeCore0(void *arg);
void taskCodeCore1(void *arg);
int map(int x, int in_min, int in_max, int out_min, int out_max);

TaskHandle_t xHandle = NULL;

adc_oneshot_unit_handle_t adc1_handle;
int result [3];

void app_main(void)
{
            ledc_channel_config_t channel_conf = {
                  .gpio_num = GPIO_NUM_15,
                  .speed_mode = LEDC_HIGH_SPEED_MODE,
                  .channel = LEDC_CHANNEL_0,
                  .intr_type = LEDC_INTR_DISABLE,
                  .timer_sel = LEDC_TIMER_0,
                  .duty = 0,
                  .hpoint = 0,
                  
            };
            ledc_channel_config(&channel_conf);

            ledc_timer_config_t ledc_conf = {
                  .speed_mode = LEDC_LOW_SPEED_MODE,
                  .duty_resolution = LEDC_TIMER_13_BIT,
                  .timer_num = LEDC_TIMER_0,
                  .freq_hz = 50,
                  .clk_cfg = LEDC_AUTO_CLK,
            };      
            ledc_timer_config(&ledc_conf);

            gpio_config_t gpio_conf = {  // gpio config struct
                  .mode = GPIO_MODE_OUTPUT,
                  .pin_bit_mask = 0B00000000000000001000000000000000,
                  .intr_type = GPIO_INTR_DISABLE,
            };

            gpio_config(&gpio_conf);
            
            // adc config : 
            adc_oneshot_unit_init_cfg_t init_config1 = {
                  .unit_id = ADC_UNIT_2,
                  .clk_src = 0,
            };

            adc_oneshot_chan_cfg_t config = {
                  .bitwidth = ADC_BITWIDTH_DEFAULT,
                  .atten = ADC_ATTEN_DB_0,
            };
            
            ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));
            ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_4, &config));
            ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_5, &config));
            ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_8, &config));

      
            xTaskCreatePinnedToCore(taskCodeCore0, "read_val", 4096, NULL, 10, &xHandle, 0);
            xTaskCreatePinnedToCore(taskCodeCore1, "output val", 4096, NULL, 10, &xHandle, 0);
}

void taskCodeCore0(void *arg){
      while(1){
            vTaskDelay(10);
            adc_oneshot_read(adc1_handle, ADC_CHANNEL_4, &result[0]);
            adc_oneshot_read(adc1_handle, ADC_CHANNEL_8, &result[1]);
            adc_oneshot_read(adc1_handle, ADC_CHANNEL_6, &result[2]);
            } 

}           
void taskCodeCore1(void *arg){
      while(1){
            vTaskDelay(10 / portTICK_PERIOD_MS);
            gpio_set_level(GPIO_NUM_15, 1);
            vTaskDelay(10 / portTICK_PERIOD_MS);
            gpio_set_level(GPIO_NUM_15, 0);
            printf("result 1 : %d result 2 : %d result 3 : %d\n", result[0], result[1], result[2]);
      }
}

int map(int x, int in_min, int in_max, int out_min, int out_max){
      
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
