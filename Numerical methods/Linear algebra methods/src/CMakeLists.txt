cmake_minimum_required(VERSION 3.1)

project(LinAlg LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/src)

enable_testing()
add_subdirectory(test)

add_executable(direct direct.cpp)
add_executable(hw2 hw2.cpp)
add_executable(iterative iterative.cpp)
add_executable(eigen eigen.cpp)
