
add_library(NeuralNetwork NeuralNetwork.cpp)

set_target_properties(NeuralNetwork PROPERTIES
	VERSION ${PROJECT_VERSION}
	PUBLIC_HEADER NeuralNetwork.h)


get_target_property(MATRIX_SOURCE_DIR Matrix SOURCE_DIR)
include_directories(${MATRIX_SOURCE_DIR})

target_link_libraries(NeuralNetwork Matrix)
