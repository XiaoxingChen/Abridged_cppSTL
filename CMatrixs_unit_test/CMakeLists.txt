cmake_minimum_required(VERSION 2.8)
project(matrix_test)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../math
	${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DARM_MATH_CM4")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DARM_MATH_CM4")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../math math)

add_executable(matrix_test main.cpp 
	arm_mat_add_f32.c 
	arm_mat_sub_f32.c 
	arm_mat_init_f32.c 
	arm_mat_inverse_f32.c 
	arm_mat_mult_f32.c
	arm_mat_scale_f32.c
	arm_mat_trans_f32.c
	Matrix.cpp
	)

target_link_libraries(matrix_test math)

