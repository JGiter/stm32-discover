#include "lib_cm4_sys_tick.h"
#include "stm32f303xe.h"
#include <stdint.h>
#include <stm32f3xx_hal_gpio.h>

void configure_led (void);
void configure_btn (void);
void configure_btn_click (void);
void configure_sys_tick (uint32_t);

SysTick_Type *sys_tick;

__attribute__ ((noreturn)) int
main (void)
{
  configure_led ();

  configure_btn ();

  configure_btn_click ();

  configure_sys_tick (1000);

  while (1)
    ;
}

void
EXTI15_10_IRQHandler (void)
{
  if ((EXTI->PR & EXTI_PR_PIF13)
      == EXTI_PR_PIF13)
    {
      SysTick_toggle ();
      // SysTick_reset ();

      EXTI->PR |= EXTI_PR_PIF13;
    }
}

void
configure_led (void)
{
  // LED A5
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  // 0x01 General purpose output mode
  GPIOA->MODER |= (0x01 << GPIO_MODER_MODER5_Pos);
  // 0x0 output push-pull
  GPIOA->OTYPER &= ~GPIO_OTYPER_OT_5;
}

void
configure_btn (void)
{
  // Button PC13
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
}

void
configure_btn_click (void)
{
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  // reset EXT13
  SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
  // map PC13->EXT13
  SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
  EXTI->RTSR |= EXTI_RTSR_TR13;
  EXTI->FTSR &= ~EXTI_FTSR_TR13;
  EXTI->IMR |= EXTI_IMR_IM13;

  NVIC_SetPriority (EXTI15_10_IRQn, 1);
  NVIC_EnableIRQ (EXTI15_10_IRQn);
}

void
configure_sys_tick (uint32_t period)
{
  SysTick_reset ();
  SysTick_set_clock_source ();
  // 3 seconds
  SysTick_set_period (period);
  // lowest priority
  NVIC_SetPriority (SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);
  NVIC_EnableIRQ (SysTick_IRQn);
}

void
SysTick_Callback (void)
{
  // toggle led
  GPIOA->ODR ^= GPIO_PIN_5;
}
