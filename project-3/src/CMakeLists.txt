add_executable(bitrev-app ./bitrev-app.cpp)
target_link_libraries(bitrev-app
	PUBLIC
	bitrev
	project-warnings
)

add_executable(br-fft-app ./br-fft-app.cpp)
target_link_libraries(br-fft-app
	PUBLIC
	complex-number
	complex-number-parser
	bitrev
	br-fft
	utils
	project-warnings
)

add_executable(benchmark ./benchmark.cpp)
target_link_libraries(benchmark
	PUBLIC
	complex-number
	complex-number-parser
	bitrev
	dft
	fft
	br-fft
	utils
	project-warnings
)
