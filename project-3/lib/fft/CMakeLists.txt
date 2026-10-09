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

add_library(rec-fft rec-fft.cpp)
target_include_directories(rec-fft PUBLIC .)
target_link_libraries(rec-fft
	PRIVATE
	project-warnings
	complex-number
)
