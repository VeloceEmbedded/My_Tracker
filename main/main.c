#include <stdio.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/ledc.h"
#include "sdkconfig.h"
#include "esp_timer.h"

// Define the log tag
static const char *TAG = "Breathing LED";

// LED configuration
const int ledPin = 2;                                   // GPIO pin
const ledc_timer_t ledTimer = LEDC_TIMER_0;
const ledc_channel_t ledChannel = LEDC_CHANNEL_0;

// Breathing effect parameters
const float one_breath = 5.0;                           // Duration of one breath in seconds
const int smoothness_pts = 100;                         // Number of steps in one breathing cycle

// Gaussian parameters
const float a = 3.8;                                    // Peak value
const float offset = 0.4;                               // Offset
const float b = 18.04;                                  // Center of the peak
const float c = 2450;                                   // Width of the bell
const int freq = 1000;                                  // PWM frequency in Hertz

void breathing_led_task(void *pvParameters) {
    // Configure the LED PWM Timer
    ledc_timer_config_t led_timer = {
        .duty_resolution = LEDC_TIMER_10_BIT,           // resolution of PWM duty
        .freq_hz = freq,                                // frequency of PWM signal
        .speed_mode = LEDC_LOW_SPEED_MODE,              // timer mode
        .timer_num = ledTimer                           // timer index
    };
    ledc_timer_config(&led_timer);

    // Configure the LED PWM Controller
    ledc_channel_config_t led_channel = {
        .channel    = ledChannel,
        .duty       = 0,
        .gpio_num   = ledPin,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_sel  = ledTimer
    };
    ledc_channel_config(&led_channel);

    for(;;) {
        //uint64_t start_time = esp_timer_get_time();
        float start_x = b - 4 * c;
        float end_x = b + 4 * c;
        float step_x = (end_x - start_x) / smoothness_pts;

        for (int i = 0; i < smoothness_pts; ++i) {
            float x = start_x + step_x * i;
            float gauss = exp(-pow(x - b, 2) / (2 * pow(c, 2)));
            float dutyCycle = offset + a * gauss;
            int pwm = (int)((dutyCycle / (offset + a)) * 1023.0);

            ledc_set_duty(LEDC_LOW_SPEED_MODE, ledChannel, pwm);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, ledChannel);

            //ESP_LOGI(TAG, "i: %d, x: %f, gauss: %f, dutyCycle: %f, pwm: %d", i, x, gauss, dutyCycle, pwm);

            vTaskDelay((int)(one_breath / smoothness_pts * 1000) / portTICK_PERIOD_MS);
        }
        //uint64_t end_time = esp_timer_get_time();
        //uint64_t executionTimeMicros_1 = end_time - start_time;
        //ESP_LOGI(TAG, "Exectution Time: %llu microseconds", executionTimeMicros_1);
    }
}

void app_main() {
    xTaskCreate(breathing_led_task, "breathing_led_task", 2048, NULL, 1, NULL);
}
