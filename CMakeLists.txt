cmake_minimum_required(VERSION 3.12)
project(Rubik_sCube)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 2)
set(VERSION_PATCH 0)

set(PROJECT_POSTFIX "-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(INSTALL_NAME "Rubik's Cube")
set(INSTALL_DIR "${PROJECT_SOURCE_DIR}/${INSTALL_NAME}-${CMAKE_SYSTEM_NAME}${PROJECT_POSTFIX}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLEW_STATIC")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PROJECT_SOURCE_DIR}/RubiksCube.res")
    set(GLEW_LIB "glew32")
    set(OPENGL_LIB "opengl32")
    set(FREETYPE_LIB "freetype")
    set(Z_LIB "z")
endif()
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie -DLINUX=1")
    set(GLEW_LIB "GLEW.a")
    set(OPENGL_LIB "GL")
    set(FREETYPE_LIB "freetype.a")
    set(Z_LIB "z.a")
endif()

file(
        GLOB srcs
        main.cpp
#        Base/FileLoader.cpp
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
        ${GLEW_LIB}
        glfw3
        ${OPENGL_LIB}
        glm_static
        ${FREETYPE_LIB}
        DLPackager
        DLFileKit
        ${Z_LIB}
)
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    link_libraries(
            pthread
            dl
            X11
            Xrandr
            Xinerama
            Xcursor
            Xxf86vm
    )
endif ()

add_executable(Rubik_sCube ${srcs})
set_target_properties(Rubik_sCube PROPERTIES OUTPUT_NAME "Rubik's Cube(Bloated)")

install(FILES working/RubiksCube.dlp DESTINATION ${PROJECT_BINARY_DIR}/bin)

if (${CMAKE_BUILD_TYPE} MATCHES "Release")
    install(TARGETS Rubik_sCube DESTINATION "${INSTALL_DIR}/bin")
    install(FILES working/RubiksCube.dlp DESTINATION ${INSTALL_DIR}/bin)
endif ()