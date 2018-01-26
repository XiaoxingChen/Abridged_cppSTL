cmake_minimum_required(VERSION 2.8)
project(odometer_test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../
	${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_USE_MATH_DEFINES")
set(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/.. odometer)

add_executable(odometer_test main.cpp)

target_link_libraries(odometer_test odometer)

