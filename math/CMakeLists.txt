cmake_minimum_required(VERSION 2.8)
aux_source_directory(. DIR_LIB_MATH)
add_library(math ${DIR_LIB_MATH})
target_link_libraries(math)
