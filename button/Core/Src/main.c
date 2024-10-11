#include "stm32f303xe.h"
#include <stdint.h>
#include <stm32f3xx_hal_gpio.h>

__attribute__ ((noreturn)) int
main (void)
{
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

  // Led PA5
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  GPIOA->MODER |= (0x01 << GPIO_MODER_MODER5_Pos);
  GPIOA->OTYPER &= ~GPIO_OTYPER_OT_5;
  // Button PC13
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

  // reset EXT13
  SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
  // map PC13->EXT13
  SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;

  EXTI->RTSR |= EXTI_RTSR_TR13;
  EXTI->FTSR &= ~EXTI_FTSR_TR13;
  EXTI->IMR |= EXTI_IMR_IM13;

  NVIC_SetPriority (EXTI15_10_IRQn, 1);
  NVIC_EnableIRQ (EXTI15_10_IRQn);

  while (1)
    ;
}

void
EXTI15_10_IRQHandler (void)
{
  if ((EXTI->PR & EXTI_PR_PIF13)
      == EXTI_PR_PIF13)
    {
      GPIOA->ODR ^= GPIO_PIN_5;

      EXTI->PR |= EXTI_PR_PIF13;
    }
}
