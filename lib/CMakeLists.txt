cmake_minimum_required(VERSION 3.2)

project(allocator_lib)

add_library(allocator_lib allocator.cpp)
add_library(container_lib container.cpp)

set_target_properties(allocator_lib container_lib PROPERTIES
	CXX_STANDART 17
	CXX_STANDART_REQUIRED ON
)

if(MSVC)
	target_compile_options(allocator_lib PRIVATE
		/W4
	)
	target_compile_options(container_lib PRIVATE
		/W4
	)
else()
	target_compile_options(allocator_lib PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
	target_compile_options(container_lib PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
endif()