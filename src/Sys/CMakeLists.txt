target_sources(
    ex_cpp_stuff
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/sys.hpp
    ${CMAKE_CURRENT_LIST_DIR}/sys.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Logger.hpp
)

target_include_directories(
    ex_cpp_stuff
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)