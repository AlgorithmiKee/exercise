#include "stm32f1xx_hal.h"

// -----------------------------------------------------------------------------
// Initialize GPIO for LED (PC13) and Button (PA0 with EXTI)
// -----------------------------------------------------------------------------
void GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // LED: PC13 as push-pull output
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // Button: PA0 as input EXTI on rising edge
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;  // or PULLUP depending on wiring
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Enable EXTI line interrupt in NVIC
    HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

// -----------------------------------------------------------------------------
// Main program
// -----------------------------------------------------------------------------
int main(void)
{
    HAL_Init();
    GPIO_Init();

    while (1)
    {
        // Nothing here — LED logic handled entirely in interrupt
    }
}

// -----------------------------------------------------------------------------
// Interrupt handler — required by HAL
// -----------------------------------------------------------------------------
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

// -----------------------------------------------------------------------------
// HAL callback — runs on button press
// -----------------------------------------------------------------------------
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_0)
    {
        // Toggle LED
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
}
