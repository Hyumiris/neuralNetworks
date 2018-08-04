cmake_minimum_required (VERSION 3.7)
set (CMAKE_CXX_STANDARD 11)

project(NeuralNetworks VERSION 0.1 LANGUAGES CXX)

add_subdirectory(src/Matrix/ "${CMAKE_CURRENT_BINARY_DIR}/Matrix")
add_subdirectory(src/NeuralNetwork/ "${CMAKE_CURRENT_BINARY_DIR}/NeuralNetwork")
add_subdirectory(Tests/ "${CMAKE_CURRENT_BINARY_DIR}/Tests")
