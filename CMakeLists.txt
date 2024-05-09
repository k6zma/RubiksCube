cmake_minimum_required(VERSION 3.27)
project(RubiksCube)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES "arm64")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(
        include
        ${OPENGL_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
)

add_executable(RubiksCube
        src/main.cpp
        src/solver/StateManager.cpp
        src/solver/CLIParameters.cpp
        src/solver/CubeSolver.cpp
        include/visual/CubeRenderer.h
)

target_link_libraries(RubiksCube
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        GLEW::GLEW
        glfw
)
