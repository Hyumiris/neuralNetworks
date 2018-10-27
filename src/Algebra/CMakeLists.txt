
add_library(Algebra
	Matrix/Matrix.cpp Vector/Vector.cpp)

set_target_properties(Algebra PROPERTIES
	VERSION ${PROJECT_VERSION})

target_include_directories(Algebra
	PUBLIC include/)
