add_library(filters filters.cpp)
target_include_directories(filters PUBLIC .)
target_link_libraries(filters
	PRIVATE
	project-warnings
	complex-number
	complex-number-parser
)
