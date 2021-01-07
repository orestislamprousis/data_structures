cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the project name
project(orla_data_structures)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vector)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/doubly_linked_list)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)