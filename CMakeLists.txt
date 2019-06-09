cmake_minimum_required(VERSION 3.13)
project(MatrixComputation)

set(CMAKE_CXX_STANDARD 11)

add_executable(MatrixComputation main.cpp MatrixCalculator.cpp MatrixCalculator.h Core/Matrix.cpp Core/Matrix.h Core/Bignum.cpp Core/Bignum.h)