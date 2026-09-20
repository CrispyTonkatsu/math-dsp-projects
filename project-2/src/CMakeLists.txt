add_executable(dft-calc ./dft-calc.cpp)
target_link_libraries(dft-calc
	PUBLIC
	project-warnings
	complex-number
	complex-number-parser
	dft
	utils
)
