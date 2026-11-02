add_executable(lowpass ./lowpass.cpp)
target_link_libraries(lowpass
	PUBLIC
	complex-number
	complex-number-parser
	bitrev
	dft
	fft
	br-fft
	utils
	filters
	project-warnings
)

add_executable(sample ./sample.cpp)
