cmake_minimum_required (VERSION 3.7)
set (CMAKE_CXX_STANDARD 11)

project(NeuralNetworks VERSION 0.1 LANGUAGES CXX)

add_subdirectory(src/Algebra/ "${CMAKE_CURRENT_BINARY_DIR}/Algebra")
add_subdirectory(src/NeuralNetwork/ "${CMAKE_CURRENT_BINARY_DIR}/NeuralNetwork")
add_subdirectory(Tests/ "${CMAKE_CURRENT_BINARY_DIR}/Tests")
