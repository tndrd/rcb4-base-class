cmake_minimum_required(VERSION 3.0)
project(Rcb4BaseClass)

add_library(rcb4base src/Rcb4BaseClass.cpp)
target_include_directories(rcb4base PUBLIC inc/)