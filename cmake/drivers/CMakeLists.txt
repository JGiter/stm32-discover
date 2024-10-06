cmake_minimum_required(VERSION 3.20)
project(stm32-hal)

set(CMSIS ${CMAKE_SOURCE_DIR}/Drivers/CMSIS)
set(CMSIS_INC ${CMSIS}/Include)

set(CMSIS_F3 ${CMSIS}/Device/ST/STM32F3xx)
set(CMSIS_F3_INC ${CMSIS_F3}/Include)

set(HAL ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver)
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
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_exti.c
)
target_include_directories(drivers
  INTERFACE ${CMAKE_SOURCE_DIR}/Core/Inc
  INTERFACE ${HAL_INC}
  INTERFACE ${CMSIS_INC}
  INTERFACE ${CMSIS_F3_INC}
)
