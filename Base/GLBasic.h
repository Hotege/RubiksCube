//
// Created by dl on 2018/11/5.
//

#ifndef RUBIK_SCUBE_GLBASIC_H
#define RUBIK_SCUBE_GLBASIC_H


#include <string>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct SHADER
{
	GLuint program, vertex, fragment;
};

GLFWwindow* RCGLInitialize(GLFWwindow** ppWnd, const int& w, const int& h, const char* title);
void RCGLSetMouseButtonCallback(GLFWwindow** ppWnd, GLFWmousebuttonfun cbfun);
void RCGLLoadShader(const std::string& strTag, const std::string& vertexFile, const std::string& fragmentFile);
void RCGLSetMainLoopCallback(void (*mainLoop)(void*));
void RCGLMainLoop(GLFWwindow** ppWnd, void* pParam);
void RCGLSetVertexParam(const std::string& strTag, const std::string& strParamName, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
void RCGLSetUniformMatrix4fv(const std::string& strTag, const std::string& strParamName, GLsizei count, GLboolean transpose, const GLfloat* value);
void RCGLSetUniform1i(const std::string& strTag, const std::string& strParamName, GLuint texTag, GLuint tex, GLuint layer);
void RCGLSetUniform4fv(const std::string& strTag, const std::string& strParamName, GLsizei count, const GLfloat* value);
void RCGLDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
void RCGLTerminate();

#endif //RUBIK_SCUBE_GLBASIC_H
