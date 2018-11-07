cmake_minimum_required(VERSION 3.12)
project(Rubik_sCube)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(PROJECT_POSTFIX "-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(INSTALL_NAME "Rubik's Cube")
set(INSTALL_DIR "${PROJECT_SOURCE_DIR}/${INSTALL_NAME}${PROJECT_POSTFIX}")

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
        ${FILEKIT_INCLUDE_DIR}
        ${PKG_INCLUDE_DIR}
        ${ZLIB_INCLUDE_DIR}
)

link_directories(
        ${CXIMAGE_LINK_DIR}
        ${GLEW_LINK_DIR}
        ${GLFW_LINK_DIR}
        ${GLM_LINK_DIR}
        ${FREETYPE_LINK_DIR}
        ${FILEKIT_LINK_DIR}
        ${PKG_LINK_DIR}
        ${ZLIB_LINK_DIR}
)

link_libraries(
        CxImage
        glew32
        glfw3
        opengl32
        glm_static
        freetype
        DLPackager
        DLFileKit
        z
)

add_executable(Rubik_sCube ${srcs})
set_target_properties(Rubik_sCube PROPERTIES OUTPUT_NAME "Rubik's Cube(Bloated)")

install(FILES working/RubiksCube.dlp DESTINATION ${PROJECT_BINARY_DIR}/bin)

if (${CMAKE_BUILD_TYPE} MATCHES "Release")
    install(TARGETS Rubik_sCube DESTINATION "${INSTALL_DIR}/bin")
    install(FILES working/RubiksCube.dlp DESTINATION ${INSTALL_DIR}/bin)
endif ()