target_sources(
    ex_cpp_stuff
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/containers.hpp
    ${CMAKE_CURRENT_LIST_DIR}/containers.cpp
)

target_include_directories(
    ex_cpp_stuff
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)