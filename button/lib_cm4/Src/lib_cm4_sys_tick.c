#include "lib_cm4_sys_tick.h"
#include "stm32f303xe.h"
#include "stm32f3xx_hal_cortex.h"
#include "stm32f3xx_hal_def.h"
#include "stm32f3xx_hal_gpio.h"
#include "system_stm32f3xx.h"
#include <stdint.h>

__weak void
SysTick_Callback (void)
{
}

/**
 * @brief  Disables timer and its interrupts
 */
void
SysTick_reset (void)
{
  SysTick->CTRL = 0;
}

/**
 * @brief  Sets lowest priority of SysTick interrupt and enebles timer.
 */
void
SysTick_start (void)
{
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void
SysTick_toggle (void)
{
  SysTick->CTRL ^= SysTick_CTRL_TICKINT_Msk;
  SysTick->CTRL ^= SysTick_CTRL_ENABLE_Msk;
}

// TODO: specify clock source
int
SysTick_set_clock_source (void)
{
  // SysTick_Type *SysTick = (SysTick_Type *)SysTick_BASE;

  // if (clksrc == HCLK_DIV8)
  // {
  // HAL_SYSTICK_CLKSourceConfig ();
  SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK_DIV8;
  // SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
  // }
  // else if (clksrc == HFCLK)
  //   {
  //     SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
  //   }
  // else
  //   {
  //     return -1;
  //   }

  return 0;
}

/**
 * @param uint32_t *period tick period in millyseconds.
 */
void
SysTick_set_period (uint32_t period)
{
  uint32_t SystemCoreClock = 8000000;

  uint32_t counts;

  // HFCLK
  if ((SysTick->CTRL & SysTick_CTRL_CLKSOURCE_Msk) == SysTick_CTRL_CLKSOURCE_Msk)
    {
      counts = (period / 1000) * SystemCoreClock;
    }
  // HFCLK_DIV8
  else
    {
      counts = (period / 1000) * (SystemCoreClock >> 3);
    }

  SysTick->VAL = 0;
  // reload value has 24 bits
  SysTick->LOAD = ((counts - 1) & 0x00FFFFFF);
}

void
SysTick_Handler (void)
{
  SysTick_Callback ();
}
