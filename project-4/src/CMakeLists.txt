add_executable(lowpass ./lowpass.cpp)
target_link_libraries(lowpass
	PUBLIC
	complex-number
	utils
	filters
	project-warnings
)
