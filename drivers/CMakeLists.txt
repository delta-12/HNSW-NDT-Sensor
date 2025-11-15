cmake_minimum_required(VERSION 3.30)
project(Drivers)

option(DRIVER_A4988 "Enable A4988 driver" OFF)

if(DRIVER_A4988)
    message(STATUS "A4988 driver enabled.")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/a4988)
endif()

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        $<$<TARGET_EXISTS:A4988>:A4988>
)