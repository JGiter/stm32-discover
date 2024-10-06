cmake_minimum_required(VERSION 3.20)

set(target blink)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

include(cmake/arm-none-eabi-gcc.cmake)

project(${target})
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_executable(${target} ${CMAKE_SOURCE_DIR}/Core/Src/main.c)

add_subdirectory(cmake/drivers)

target_link_libraries(${target} drivers)

add_custom_command(TARGET ${target}  POST_BUILD
  COMMENT "Extract  : assembly list file  : from ${target}.elf"
  COMMAND arm-none-eabi-objdump -h -S -s $<TARGET_FILE:${target}>  > $<TARGET_FILE_DIR:${target}>/${target}.lss
)
