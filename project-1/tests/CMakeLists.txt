enable_testing()
add_executable(test-hw1 test-main.cpp)
target_include_directories(test-hw1 PRIVATE ./src)
target_link_libraries(test-hw1
	PRIVATE
	project_warnings
	complex-number
	complex-number-parser
)

add_test(NAME unit-tests COMMAND test-hw1)
