cmake_minimum_required(VERSION 3.10)
project(cGraphicalManipulator C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(cGraphicalManipulator
    src/cGraphicalManipulator.c
    src/stb_image.c
    src/stb_image_write.c
)
target_include_directories(cGraphicalManipulator PRIVATE
    libs
    libs/external
)
add_custom_command(
    TARGET cGraphicalManipulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:cGraphicalManipulator>/assets
)
install(TARGETS cGraphicalManipulator
    DESTINATION /usr/local/bin
)
install(DIRECTORY include/ 
    DESTINATION /usr/local/include
)
install(DIRECTORY assets/ 
    DESTINATION /usr/local/share/cGraphicalManipulator
)