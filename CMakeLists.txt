cmake_minimum_required(VERSION 3.10)

project(LlglGui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    -Wall -Wextra -Werror
    -Wno-error=unused-function -Wno-error=unused-variable
    -Wno-unused-parameter -Wno-sign-compare
)

cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

file(GLOB SOURCES
    "src/*.cpp"
    "glad/src/*.c"
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} 
PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/stb
PRIVATE
    ${OPENGL_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    OpenGL::GL
    glfw
    glm::glm
)

add_definitions(${OPENGL_DEFINITIONS})


