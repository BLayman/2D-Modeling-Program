cmake_minimum_required(VERSION 2.8)
project (project_1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../lib/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)

include_directories(../lib/glfw/include)
include_directories(../lib/glad/include)
include_directories(../lib/csci441/include)
include_directories(../lib/glm/glm)

set(LAB program1)
add_executable(${LAB} main.cpp ../lib/glad/src/glad.c GameState.h GameState.cpp Matrix.cpp Matrix.h Vector3.cpp Vector3.h keyHandler.h overloading.h shapes.h model.cpp model.h overloading.cpp ModelHandler.h Selector.h CustomShape.h CustomShape.cpp)
target_link_libraries(${LAB} glfw ${GLFW_LIBRARIES})

