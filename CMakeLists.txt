cmake_minimum_required(VERSION 3.30)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message("Build type: " ${CMAKE_BUILD_TYPE})

# Set board
if(NOT BOARD)
    set(BOARD "Nucleo-64")
endif()
message("Board: " ${BOARD})

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Project with support for ASM and C languages
project(HNSW_NDE_Sensor LANGUAGES C ASM)

# Collection functions
include(${CMAKE_SOURCE_DIR}/collect.cmake)

################################################################################
# Subdirectories
################################################################################
add_subdirectory(${CMAKE_SOURCE_DIR}/boards)
add_subdirectory(${CMAKE_SOURCE_DIR}/drivers)

################################################################################
# Sensor firmware
################################################################################
set(SENSOR_DIR ${CMAKE_SOURCE_DIR}/sensor)
set(SENSOR_INC_DIR ${SENSOR_DIR}/inc)
set(SENSOR_SRC_DIR ${SENSOR_DIR}/src)

set(SENSOR_SRCS
    ${SENSOR_SRC_DIR}/cobs.c
    ${SENSOR_SRC_DIR}/main.c
    ${SENSOR_SRC_DIR}/sensor.c
)

set_source_files_properties(
    ${SENSOR_SRCS}
    PROPERTIES
    COMPILE_OPTIONS "-Werror"
)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${SENSOR_INC_DIR}
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${SENSOR_SRCS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Bsp
        Drivers
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_SIZE} "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.elf"
        COMMAND ${CMAKE_OBJCOPY} -O ihex "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.elf" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.hex"
        COMMAND ${CMAKE_OBJCOPY} -O binary -S "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.elf" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.bin"
)

if(COMMAND collect_sources)
    collect_sources(${PROJECT_NAME})
endif()
if(COMMAND collect_include_directories)
    collect_include_directories(${PROJECT_NAME})
endif()

################################################################################
# CI and tools
################################################################################
set(TOOLS_DIR ${CMAKE_SOURCE_DIR}/tools)
get_property(CPPCHECK_SOURCES GLOBAL PROPERTY SOURCE_COLLECTION)
get_property(UNCRUSTIFY_INC_DIRS GLOBAL PROPERTY INCLUDE_DIRECTORIES_COLLECTION)
if (CPPCHECK_SOURCES)
    include(${TOOLS_DIR}/cppcheck/cppcheck.cmake)
endif()
if (CPPCHECK_SOURCES AND UNCRUSTIFY_INC_DIRS)
    set(UNCRUSTIFY_SOURCES ${CPPCHECK_SOURCES})
    include(${TOOLS_DIR}/uncrustify/uncrustify.cmake)
endif()