cmake_minimum_required(VERSION 2.8)
aux_source_directory(. DIR_LIB_ODOMETER)
add_library(odometer ${DIR_LIB_ODOMETER})
target_link_libraries(odometer)
