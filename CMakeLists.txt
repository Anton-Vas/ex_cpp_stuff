cmake_minimum_required(VERSION 3.20.0)
project(ex_cpp_stuff VERSION 0.1.0)

# Main
add_executable(ex_cpp_stuff main.cpp)


# ~~~~~~ 'root' path ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
set(ROOT /home/dev/Desktop/ex_cpp_stuff)

# ~~~~~~ C++  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
set(CMAKE_CXX_STANDARD_REQUIRED 20)                             # C++ version

find_package(Threads REQUIRED)                                  # C++ thread lib
target_link_libraries(${CMAKE_PROJECT_NAME} Threads::Threads)

# ~~~~~~ CTest ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
include(CTest)
enable_testing()

# ~~~~~~ Folders ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
add_subdirectory(src)

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


message("\n####################################################################################\n")
message("> BUILD INFO")
message("       NAME:           " ${PROJECT_NAME})
message("       ROOT:           " ${ROOT})
message("       CMAKE version:  " ${CMAKE_VERSION})
message("\n####################################################################################\n")