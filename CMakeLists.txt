cmake_minimum_required(VERSION 3.12)
project(Rubik_sCube)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLEW_STATIC")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PROJECT_SOURCE_DIR}/RubiksCube.res")
endif()

file(
        GLOB srcs
        main.cpp
        Base/FileLoader.cpp
        Base/GLBasic.cpp
        Base/RCButton.cpp
        GameLogic/Cube.cpp
        GLCode.cpp
)

include_directories(
        ${PROJECT_SOURCE_DIR}

        C:/Users/dl/Documents/glew-2.1.0/include
        C:/Users/dl/Documents/glfw-3.2.1/include
        C:/Users/dl/Documents/glm
        C:/Users/dl/Documents/freetype-2.9.1/include
)

link_directories(
        C:/Users/dl/Documents/glew-2.1.0/lib
        C:/Users/dl/Documents/glfw-3.2.1/build-mingw/src
        C:/Users/dl/Documents/glm/build-MinGW/glm
        C:/Users/dl/Documents/freetype-2.9.1/build-MinGW
)

link_libraries(
        glew32
        glfw3
        opengl32
        glm_static
        freetype
)

add_executable(Rubik_sCube ${srcs})
set_target_properties(Rubik_sCube PROPERTIES OUTPUT_NAME "Rubik's Cube(Bloated)")

install(FILES working/button.vs DESTINATION ${PROJECT_BINARY_DIR}/bin)
install(FILES working/button.fs DESTINATION ${PROJECT_BINARY_DIR}/bin)
install(FILES working/cube.vs DESTINATION ${PROJECT_BINARY_DIR}/bin)
install(FILES working/cube.fs DESTINATION ${PROJECT_BINARY_DIR}/bin)
install(FILES working/mingliu.ttc DESTINATION ${PROJECT_BINARY_DIR}/bin)