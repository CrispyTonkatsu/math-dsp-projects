add_library(dft dft.cpp)
target_include_directories(dft PUBLIC .)
target_link_libraries(dft
	PRIVATE
	project-warnings
	complex-number
)

add_library(fft fft.cpp)
target_include_directories(fft PUBLIC .)
target_link_libraries(fft
	PRIVATE
	project-warnings
	complex-number
)

add_library(br-fft br-fft.cpp)
target_include_directories(br-fft PUBLIC .)
target_link_libraries(br-fft
	PRIVATE
	project-warnings
	complex-number
	bitrev
)
