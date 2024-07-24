cmake_minimum_required(VERSION 3.0)
project(Rcb4BaseClass)

add_library(rcb4base_impl src/Rcb4BaseClass.cpp)
target_include_directories(rcb4base_impl PUBLIC inc/)

add_library(rcb4base_mock src/Rcb4BaseClassMock.cpp)
target_include_directories(rcb4base_mock PUBLIC inc/)
