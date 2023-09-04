
add_subdirectory(Containers)
add_subdirectory(Sys)
add_subdirectory(Patterns)

target_include_directories(
    ex_cpp_stuff
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)