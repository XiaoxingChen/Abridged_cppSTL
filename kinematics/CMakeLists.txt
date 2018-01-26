cmake_minimum_required(VERSION 2.8)
aux_source_directory(. DIR_LIB_ODOMETER)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/odometer_unit_test
	${CMAKE_CURRENT_SOURCE_DIR})
add_library(odometer ${DIR_LIB_ODOMETER})
target_link_libraries(odometer)
