
add_executable(Tests tests.cpp)

set_target_properties(Tests PROPERTIES
	VERSION ${PROJECT_VERSION})

get_target_property(MATRIX_SOURCE_DIR Matrix SOURCE_DIR)
include_directories(${MATRIX_SOURCE_DIR})

get_target_property(NEURALNETWORK_SOURCE_DIR NeuralNetwork SOURCE_DIR)
include_directories(${NEURALNETWORK_SOURCE_DIR})

include_directories(../src/Testing)

target_link_libraries(Tests NeuralNetwork)
