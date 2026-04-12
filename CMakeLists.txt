cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(flappy-bird)

add_subdirectory("vendor/glfw")

set(SOURCE
    src/main.cpp
    vendor/stb_image/stb_image.cpp
    src/primitives/ArrayBuffer.cpp
    src/primitives/ArrayBuffer.h
    src/primitives/IndexBuffer.h
    src/primitives/IndexBuffer.cpp
    src/util/Shader.h
    src/util/Shader.cpp
    src/util/Texture.h
    src/util/Texture.cpp
    src/primitives/VertexArray.h
    src/primitives/VertexArray.cpp
    src/primitives/Mesh.h
    src/primitives/Mesh.cpp
    src/Event.h
    src/Event.cpp
    src/Object.h
    src/Bird.h
    src/Bird.cpp
    src/Window.h
    src/Window.cpp)

# GLAD setup
set(GLAD_SOURCES_DIR "${PROJECT_SOURCE_DIR}/vendor/glad/")
add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)
glad_add_library(glad_gl_core_33 REPRODUCIBLE API gl:core=3.3)

add_executable(${PROJECT_NAME} ${SOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include
                                                   ${PROJECT_SOURCE_DIR}/vendor)

# include GLM
set(GLM_SOURCE_DIR "${PROJECT_SOURCE_DIR}/vendor/glm/")
add_subdirectory(${GLM_SOURCE_DIR} glm_cmake)

target_link_libraries(${PROJECT_NAME} PUBLIC glad_gl_core_33 glfw glm::glm)
