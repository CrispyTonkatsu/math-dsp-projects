add_executable(pluck ./pluck.cpp)
target_link_libraries(pluck
 PUBLIC
 complex-number
 utils
 filters
 project-warnings
)
