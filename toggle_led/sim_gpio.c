#ifdef __SIMULATOR__
#include "gpio_if.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIM_EVENT_QUEUE_SIZE 32

static button_cb_t g_cb = NULL;
static bool g_led_state = false;

/* small ring buffer of events */
typedef enum { EV_BUTTON_PRESS } sim_event_t;
static sim_event_t g_queue[SIM_EVENT_QUEUE_SIZE];
static int g_q_head = 0;
static int g_q_tail = 0;
static bool g_use_queue = true; /* set false to call callback synchronously */

void gpio_if_init(void)
{
    g_led_state = false;
    g_q_head = g_q_tail = 0;
    /* print for test visibility */
    printf("[sim] gpio_if_init\n");
}

void gpio_if_led_set(bool on) {
    g_led_state = on;
}
void gpio_if_led_toggle(void) {
    g_led_state = !g_led_state;
}
bool gpio_if_led_get(void) {
    return g_led_state;
}

void gpio_if_register_button_callback(button_cb_t cb) {
    g_cb = cb;
}

/* Simulator helper: inject an event */
void sim_inject_button_press(void)
{
    if (!g_use_queue) {
        /* immediate: call callback synchronously */
        if (g_cb) {
            g_cb();
        }
        return;
    }
    int next = (g_q_tail + 1) % SIM_EVENT_QUEUE_SIZE;
    if (next == g_q_head) {
        printf("[sim] warning: event queue full, dropping event\n");
        return;
    }
    g_queue[g_q_tail] = EV_BUTTON_PRESS;
    g_q_tail = next;
}

/* Process all queued events (call in test harness to simulate ISR handling) */
void sim_process_events(void)
{
    while (g_q_head != g_q_tail) {
        sim_event_t ev = g_queue[g_q_head];
        g_q_head = (g_q_head + 1) % SIM_EVENT_QUEUE_SIZE;
        if (ev == EV_BUTTON_PRESS) {
            /* In real MCU this would be called from ISR context.
               In our host sim we call callback directly; if you want to
               simulate concurrency you can spawn a thread or set a flag. */
            if (g_cb) g_cb();
        }
    }
}

/* Reset sim state */
void sim_reset(void)
{
    g_led_state = false;
    g_q_head = g_q_tail = 0;
    g_use_queue = true;
}

#endif /* __SIMULATOR__ */
