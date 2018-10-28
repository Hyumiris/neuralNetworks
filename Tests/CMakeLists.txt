
add_executable(Tests tests.cpp
	MatrixTests.cpp VectorTests.cpp NeuralNetworkTests.cpp)

set_target_properties(Tests PROPERTIES
	VERSION ${PROJECT_VERSION})

get_target_property(ALGEBRA_INCLUDE_DIRECTORIES Algebra INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(Tests
	PRIVATE ${ALGEBRA_INCLUDE_DIRECTORIES})

get_target_property(NEURALNETWORK_INCLUDE_DIRECTORIES NeuralNetwork INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(Tests
	PRIVATE ${NEURALNETWORK_INCLUDE_DIRECTORIES})

target_include_directories(Tests 
	PRIVATE ../src/Testing)

target_link_libraries(Tests Algebra NeuralNetwork)
