cmake_minimum_required(VERSION 3.5)
enable_testing()

project(TPCC LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -Wall -pedantic -Wextra -D_GLIBCXX_DEBUG")

include_directories(include)

add_subdirectory(tests)
add_subdirectory(doc)

# add_executable(TensorEnumeration main.cpp)
