
add_library(Matrix Matrix.cpp Vector.cpp)

set_target_properties(Matrix PROPERTIES
	VERSION ${PROJECT_VERSION}
	PUBLIC_HEADER Matrix.h)
