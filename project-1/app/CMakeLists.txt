add_library(utils utils.cpp)
target_include_directories(utils PUBLIC .)
target_link_libraries(utils
	PRIVATE
	project-warnings
	complex-number
	complex-number-parser
)

add_executable(rotate rotate.cpp)
target_link_libraries(rotate
	PRIVATE
	project-warnings
	complex-number
	complex-number-parser
	utils
)
