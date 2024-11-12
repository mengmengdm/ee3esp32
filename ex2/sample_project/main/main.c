#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h" // 添加这个头文件

#define GPIO_INPUT_PIN 9// Example input pin (connected to the infrared sensor)
#define GPIO_OUTPUT_PIN 38 // Example output pin

// Interrupt Service Routine (ISR) for input pin
void IRAM_ATTR gpio_isr_handler(void* arg) {
    // Set the output pin to low when the ISR is triggered
    gpio_set_level(GPIO_OUTPUT_PIN, 0);
}

void app_main(void) {
    // Configure output pin
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;        // Disable interrupt for the output pin
    io_conf.mode = GPIO_MODE_OUTPUT;              // Set as output mode
    io_conf.pin_bit_mask = (1ULL << GPIO_OUTPUT_PIN); // Select output pin
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; // Disable pull-down
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;     // Disable pull-up
    gpio_config(&io_conf);

    // Configure input pin
    io_conf.intr_type = GPIO_INTR_NEGEDGE;         // Trigger on falling edge (e.g., when infrared sensor detects something)
    io_conf.mode = GPIO_MODE_INPUT;                // Set as input mode
    io_conf.pin_bit_mask = (1ULL << GPIO_INPUT_PIN); // Select input pin
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;  // Disable pull-down
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;      // Disable pull-up
    gpio_config(&io_conf);

    // Install the ISR service
    gpio_install_isr_service(0);

    // Attach the ISR handler to the input pin
    gpio_isr_handler_add(GPIO_INPUT_PIN, gpio_isr_handler, NULL);

    // Initial state of the output pin
    gpio_set_level(GPIO_OUTPUT_PIN, 1); // Set output pin to high initially

    printf("System ready. Waiting for infrared sensor input...\n");
}
