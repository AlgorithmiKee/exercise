#ifdef REAL_BOARD
#include "gpio_if.h"
#include "stm32f1xx_hal.h" /* change to your family */
#include <string.h>

static button_cb_t g_cb = NULL;

/* Initialize LED (PC13) and Button (PA0) as in your original program */
void gpio_if_init(void)
{
    /* HAL init done elsewhere */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;

    /* LED PC13 */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

    /* Button PA0 as EXTI on rising */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void gpio_if_led_set(bool on) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
void gpio_if_led_toggle(void) {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}
bool gpio_if_led_get(void) {
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET;
}
void gpio_if_register_button_callback(button_cb_t cb) {
    g_cb = cb;
}

/* Hook into EXTI IRQ handlers */
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_0 && g_cb) {
        g_cb();
    }
}
#endif /* REAL_BOARD */
