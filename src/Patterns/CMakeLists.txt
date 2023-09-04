target_sources(
    ex_cpp_stuff
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/patterns.hpp
    ${CMAKE_CURRENT_LIST_DIR}/patterns.cpp
)

target_include_directories(
    ex_cpp_stuff
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)