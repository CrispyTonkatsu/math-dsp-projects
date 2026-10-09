add_library(bitrev bitrev.cpp)
target_include_directories(bitrev PUBLIC .)
target_link_libraries(bitrev
	PRIVATE
	project-warnings
)
