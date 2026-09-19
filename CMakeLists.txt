cmake_minimum_required(VERSION 3.16)
project(ArabicClock VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
	src/clock_digital.cpp
	src/screen.cpp
	src/main.cpp
	src/common.cpp
	src/background_snow.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(arabic_clock ${SOURCES})

target_compile_options(arabic_clock PRIVATE -Wall -Wextra)
