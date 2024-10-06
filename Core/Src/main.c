#include "stm32f303xe.h"
#include "stm32f3xx.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_def.h"
// #include "stm32f3xx_hal_rcc.h"
// #include <main.h>
// #include <stdint.h>
#include <stdint.h>
#include <stm32f3xx_hal_gpio.h>

extern void _estack (void);
int _reset (void);
void delay (uint32_t);

uint32_t *vector_table[16 + 84] __attribute__ ((section (".isr_vector"))) = {
  (uint32_t *)_estack,
  (uint32_t *)_reset
};

__attribute__ ((noreturn)) int
_reset (void)
{
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  GPIOA->MODER |= (0x01 << GPIO_MODER_MODER5_Pos); // output mode
  GPIOA->OTYPER &= ~GPIO_OTYPER_OT_5;              // push-pull

  // __HAL_RCC_GPIOA_CLK_ENABLE ();
  // GPIO_TypeDef GPIOA_Def;
  // GPIOA_Def.MODER = MODE_OUTPUT;
  // GPIOA_Def.OTYPER = OUTPUT_PP;
  // GPIO_InitTypeDef GPIOA_InitDef;
  // GPIOA_InitDef.Pin = GPIO_PIN_5;
  // GPIOA_InitDef.Mode = GPIO_MODE_OUTPUT_PP;
  // HAL_GPIO_Init (GPIOA, &GPIOA_InitDef);

  while (1)
    {
      // HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_5);
      // HAL_Delay (2000);
      // HAL_GPIO_TogglePin (GPIOA, GPIO_PIN_5);
      uint32_t SHORT_DELAY = (1 << 20);
      uint32_t LONG_DELAY = (SHORT_DELAY << 2);

      GPIOA->ODR |= GPIO_PIN_5;
      delay (SHORT_DELAY);
      GPIOA->ODR ^= GPIO_PIN_5;
      delay (LONG_DELAY);
    }
}

void
delay (uint32_t count)
{
  while (count--)
    ;
}
