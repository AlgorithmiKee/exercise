#include "gpio_if.h"
#include <stdio.h>

/* Application state or logic can live here. For the toy example we simply
   toggle the LED when the button is pressed. */
static void button_pressed_cb(void)
{
    /* In a real app you might handle debouncing here or call a state machine. */
    gpio_if_led_toggle();
    /* For demonstrative output on host */
#ifdef __SIMULATOR__
    printf("[app] button pressed handler: LED is now %s\n", gpio_if_led_get() ? "ON" : "OFF");
#endif
}

int app_init(void)
{
    gpio_if_init();
    gpio_if_register_button_callback(button_pressed_cb);
    return 0;
}

/* Example main for embedded (real board) */
#if defined(REAL_BOARD)
int main(void)
{
    /* HAL init, clocks etc. */
    app_init();
    while (1) {
        /* app does not poll; real hardware uses EXTI interrupt to call callback */
    }
}
#endif
