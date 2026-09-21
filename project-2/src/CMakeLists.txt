add_executable(dft-calc ./dft-calc.cpp)
target_link_libraries(dft-calc
	PUBLIC
	project-warnings
	complex-number
	complex-number-parser
	dft
	utils
)

add_executable(fft-calc ./fft-calc.cpp)
target_link_libraries(fft-calc
	PUBLIC
	project-warnings
	complex-number
	complex-number-parser
	fft
	utils
)
