add_library(dft dft.cpp)
target_include_directories(dft PUBLIC .)
target_link_libraries(dft
	PRIVATE
	project-warnings
	complex-number
	complex-number-parser
)

add_library(fft fft.cpp)
target_include_directories(fft PUBLIC .)
target_link_libraries(fft
	PRIVATE
	project-warnings
	complex-number
	complex-number-parser
)
