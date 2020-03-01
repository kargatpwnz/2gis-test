cmake_minimum_required(VERSION 3.9)
project(2gis-test)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.58.0 COMPONENTS program_options REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(2gis-test main.cpp tree.cpp)
target_link_libraries(2gis-test ${Boost_LIBRARIES})
target_compile_options(2gis-test PRIVATE -Wpedantic -Wall -Werror)
