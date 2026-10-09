add_library(utils utils.cpp)
target_include_directories(utils PUBLIC .)
target_link_libraries(utils
	PRIVATE
	project-warnings
	complex-number
	complex-number-parser
)
