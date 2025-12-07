cmake_minimum_required(VERSION 3.30)
project(Nucleo-64)

################################################################################
# BSP
################################################################################
set(BSP_GPIO ON CACHE BOOL "Enable BSP GPIO")
set(BSP_PWM ON CACHE BOOL "Enable BSP PWM")
set(BSP_TIMER ON CACHE BOOL "Enable BSP timers")
set(BSP_UART ON CACHE BOOL "Enable BSP UART")

################################################################################
# Drivers
################################################################################
set(DRIVER_A4988 ON CACHE BOOL "Enable A4988 driver")