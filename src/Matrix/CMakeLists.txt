
add_library(Matrix Matrix.cpp)

set_target_properties(Matrix PROPERTIES
	VERSION ${PROJECT_VERSION}
	PUBLIC_HEADER Matrix.h)
