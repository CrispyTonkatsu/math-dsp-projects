add_executable(bitrev-app ./bitrev-app.cpp)
target_link_libraries(bitrev-app
	PUBLIC
	bitrev
	project-warnings
)
