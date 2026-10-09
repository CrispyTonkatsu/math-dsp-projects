add_library(complex-number
	complex.cpp
)
target_include_directories(complex-number PUBLIC .)
target_link_libraries(complex-number
	PUBLIC
	project-warnings
)

add_library(complex-number-parser
	parser.cpp
	tokenizer.cpp
)
target_include_directories(complex-number-parser PUBLIC .)
target_link_libraries(complex-number-parser
	PUBLIC
	project-warnings
	complex-number
)
