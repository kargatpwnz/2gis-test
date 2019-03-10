cmake_minimum_required(VERSION 3.9)
project(2gis-test)

add_executable(2gis-test main.cpp tree.cpp tree.h)

target_compile_features(2gis-test PRIVATE cxx_std_17)
target_compile_options(2gis-test PRIVATE -Wpedantic -Wall)