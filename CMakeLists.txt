cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(flappy-bird)

add_subdirectory("vendor/glfw")

set(SOURCE src/main.cpp vendor/stb_image/stb_image.cpp)

# GLAD setup
set(GLAD_SOURCES_DIR "${PROJECT_SOURCE_DIR}/vendor/glad/")
add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)
glad_add_library(glad_gl_core_33 REPRODUCIBLE API gl:core=3.3)

add_executable(${PROJECT_NAME} ${SOURCE})

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC glad_gl_core_33 glfw)
