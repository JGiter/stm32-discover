#ifndef __LIB_CM4_SYS_TICK_H
#define __LIB_CM4_SYS_TICK_H

#include <stdint.h>
// typedef enum
// {
//   HCLK_DIV8,
//   HFCLK
// } SYS_TICK_CLKSRC;

void
SysTick_reset (void);

void
SysTick_start (void);

void SysTick_toggle (void);

int
SysTick_set_clock_source (void);

void SysTick_set_period (uint32_t);

#endif // !__LIB_CM4_SYS_TICK_H
