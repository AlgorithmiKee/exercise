#ifndef GPIO_IF_H
#define GPIO_IF_H

#include <stdint.h>
#include <stdbool.h>

/* Application uses this type for button callback */
typedef void (*button_cb_t)(void);

/* Initialize HW/backend */
void gpio_if_init(void);

/* LED control: set on/off or toggle */
void gpio_if_led_set(bool on);
void gpio_if_led_toggle(void);
bool gpio_if_led_get(void); /* for tests/inspection */

/* Register button callback (application registers here) */
void gpio_if_register_button_callback(button_cb_t cb);

/* Simulator-only helpers (weak/optional on embedded build) */
#ifdef __SIMULATOR__
/* inject one button press event (immediate or queued depending on sim mode) */
void sim_inject_button_press(void);

/* process queued events (if queueing mode used) */
void sim_process_events(void);

/* clear simulator state */
void sim_reset(void);
#endif

#endif /* GPIO_IF_H */
