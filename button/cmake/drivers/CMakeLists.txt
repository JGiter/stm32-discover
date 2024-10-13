cmake_minimum_required(VERSION 3.20)
project(stm32-hal)

cmake_path(SET DRIVERS NORMALIZE "${CMAKE_SOURCE_DIR}/../Drivers")
cmake_path(SET LIB_CM4 "${CMAKE_SOURCE_DIR}/lib_cm4")

set(CMSIS ${DRIVERS}/CMSIS)
set(CMSIS_INC ${CMSIS}/Include)

set(CMSIS_F3 ${CMSIS}/Device/ST/STM32F3xx)
set(CMSIS_F3_INC ${CMSIS_F3}/Include)

set(HAL ${DRIVERS}/STM32F3xx_HAL_Driver)
set(HAL_SRC ${HAL}/Src)
set(HAL_INC ${HAL}/Inc)


add_library(drivers INTERFACE)

target_compile_definitions(drivers INTERFACE
  # USE_HAL_DRIVER
  STM32F303xE
  $<$<CONFIG:Debug>:DEBUG>
)

target_sources(drivers INTERFACE
    ${CMAKE_SOURCE_DIR}/Core/Src/main.c
    ${CMAKE_SOURCE_DIR}/Core/Src/system.c
    ${CMAKE_SOURCE_DIR}/startup.s
    ${LIB_CM4}/Src/lib_cm4_sys_tick.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c
    ${DRIVERS}/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.c
)
target_include_directories(drivers INTERFACE
  ${CMAKE_SOURCE_DIR}/Core/Inc
  ${LIB_CM4}/Include
  ${HAL_INC}
  ${CMSIS_INC}
  ${CMSIS_F3_INC}
)
