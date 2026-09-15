cmake_minimum_required(VERSION 4.3)
project(hw1 VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(
	CMAKE_C_STANDARD_INCLUDE_DIRECTORIES
	${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES}
)
set(
	CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES
	${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES}
)

add_library(project_warnings INTERFACE)

if(MSVC)
	target_compile_options(project_warnings INTERFACE /W4 /WX)
else()
	target_compile_options(project_warnings INTERFACE
		-Werror
		-Wall
		-Wextra
		-pedantic
		-Wold-style-cast
		-Woverloaded-virtual
		-Wsign-promo
		-Wctor-dtor-privacy
		-Wnon-virtual-dtor
		-Wreorder
		-fdiagnostics-color=always
	)
endif()


add_subdirectory(./src)
add_subdirectory(./tests)
