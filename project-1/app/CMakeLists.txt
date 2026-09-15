add_library(utils utils.cpp)
target_include_directories(utils PUBLIC .)
target_link_libraries(utils
	PRIVATE
	project-warnings
	complex-number
	complex-number-parser
)

add_executable(rotate rotate.cpp)
target_link_libraries(rotate
	PRIVATE
	project-warnings
	complex-number
	complex-number-parser
	utils
)

add_executable(root-sum root_sum.cpp)
target_link_libraries(root-sum
	PRIVATE
	project-warnings
	complex-number
)

add_executable(complex-dot complex_dot.cpp)
target_link_libraries(complex-dot
	PRIVATE
	project-warnings
	complex-number
	complex-number-parser
	utils
)

add_executable(unity-dot unity_dot.cpp)
target_link_libraries(unity-dot
	PRIVATE
	project-warnings
	complex-number
	complex-number-parser
	utils
)
