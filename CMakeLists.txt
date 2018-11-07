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

        ${CXIMAGE_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        ${GLM_INCLUDE_DIR}
        ${FREETYPE_INCLUDE_DIR}
)

link_directories(
        ${CXIMAGE_LINK_DIR}
        ${GLEW_LINK_DIR}
        ${GLFW_LINK_DIR}
        ${GLM_LINK_DIR}
        ${FREETYPE_LINK_DIR}
)

link_libraries(
        CxImage
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
install(FILES RubiksCube.ico DESTINATION ${PROJECT_BINARY_DIR}/bin)