/* LEDC (LED Controller) basic example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"

// 
#define UART_NUM UART_NUM_0
#define BUF_SIZE (1024)
#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (6) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY_MIN           (2000) // 最小角度对应的占空比
#define LEDC_DUTY_MAX           (4000) // 最大角度对应的占空比
#define STEP_DELAY_MS           (20)   // 每步延时20ms，控制步进速度
#define LEDC_FREQUENCY          (50) // Frequency in Hertz. Set frequency at 4 kHz

static const char *TAG = "SerialDebug";

/* Warning:
 * For ESP32, ESP32S2, ESP32S3, ESP32C3, ESP32C2, ESP32C6, ESP32H2, ESP32P4 targets,
 * when LEDC_DUTY_RES selects the maximum duty resolution (i.e. value equal to SOC_LEDC_TIMER_BIT_WIDTH),
 * 100% duty cycle is not reachable (duty cannot be set to (2 ** SOC_LEDC_TIMER_BIT_WIDTH)).
 */
// 步进函数，用于控制伺服逐步移动

void delay_1ms(int ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}


static void example_ledc_init(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_DUTY_RES,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 4 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void app_main(void)
{
    ESP_LOGI(TAG, "Hello, ESP32! Serial Debugging Initialized.");
    // Set the LEDC peripheral configuration
    example_ledc_init();
    printf("program start");
    int speed1 = 300;
    int speed2 = 1100;
    while(1){
    
    ESP_LOGI(TAG, "start");
    
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, speed1));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
    delay_1ms(1000);
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, speed2));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
    delay_1ms(1000);
    
    }
        

        // printf("Moving to minimum position\n");
        // servo_step_to(LEDC_DUTY_MIN);
        // delay_1ms(1000); // 停留在最小位置

        // printf("Moving to maximum position\n");
        // servo_step_to(LEDC_DUTY_MAX);
        // delay_1ms(1000); // 停留在最大位置
}
