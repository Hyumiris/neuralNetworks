
add_library(NeuralNetwork src/NeuralNetwork.cpp)

set_target_properties(NeuralNetwork PROPERTIES
	VERSION ${PROJECT_VERSION})

get_target_property(ALGEBRA_INCLUDE_DIRECTORIES Algebra INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(NeuralNetwork
	PRIVATE ${ALGEBRA_INCLUDE_DIRECTORIES})

target_include_directories(NeuralNetwork
	PUBLIC include/)

target_link_libraries(NeuralNetwork Algebra)
