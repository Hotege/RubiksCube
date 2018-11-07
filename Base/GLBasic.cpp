//
// Created by dl on 2018/11/5.
//

#include "GLBasic.h"
#include <vector>
#include <Base/FileLoader.h>

GLFWwindow* RCGLInitialize(GLFWwindow** ppWnd, const int& w, const int& h, const char* title)
{
	// glfw initialize
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	*ppWnd = glfwCreateWindow(w, h, title, nullptr, nullptr);
	glfwMakeContextCurrent(*ppWnd);
	glfwSwapInterval(1);
	// glew initialize
	glewInit();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
}

void RCGLSetWindowIcon(GLFWwindow** ppWnd, int count, GLFWimage* images)
{
	glfwSetWindowIcon(*ppWnd, count, images);
}

void RCGLSetMouseButtonCallback(GLFWwindow** ppWnd, GLFWmousebuttonfun cbfun)
{
	glfwSetMouseButtonCallback(*ppWnd, cbfun);
}

std::map<std::string, SHADER> m_mShader;

void RCGLLoadShader(const std::string& strTag, const std::string& vertexFile, const std::string& fragmentFile)
{
	SHADER shader = { 0 };
	GLint shaderResult = GL_FALSE;
	int shaderInfoLogLength;

	FileLoader fileVertex(vertexFile.c_str());
	shader.vertex = glCreateShader(GL_VERTEX_SHADER);
	auto pVsCode = fileVertex.GetData();
	glShaderSource(shader.vertex, 1, (const GLchar*const*)&pVsCode, nullptr);
	glCompileShader(shader.vertex);
	glGetShaderiv(shader.vertex, GL_COMPILE_STATUS, &shaderResult);
	glGetShaderiv(shader.vertex, GL_INFO_LOG_LENGTH, &shaderInfoLogLength);
	if (shaderInfoLogLength > 0)
	{
		std::vector<char> vertexShaderErrorMessage((unsigned int)(shaderInfoLogLength + 1));
		glGetShaderInfoLog(shader.vertex, shaderInfoLogLength, nullptr, &vertexShaderErrorMessage[0]);
		printf("%s\n", &vertexShaderErrorMessage[0]);
	}

	FileLoader fileFragment(fragmentFile.c_str());
	shader.fragment = glCreateShader(GL_FRAGMENT_SHADER);
	auto pFsCode = fileFragment.GetData();
	glShaderSource(shader.fragment, 1, (const GLchar*const*)&pFsCode, nullptr);
	glCompileShader(shader.fragment);
	glGetShaderiv(shader.fragment, GL_COMPILE_STATUS, &shaderResult);
	glGetShaderiv(shader.fragment, GL_INFO_LOG_LENGTH, &shaderInfoLogLength);
	if (shaderInfoLogLength > 0)
	{
		std::vector<char> fragmentShaderCubeErrorMessage((unsigned int)(shaderInfoLogLength + 1));
		glGetShaderInfoLog(shader.fragment, shaderInfoLogLength, nullptr, &fragmentShaderCubeErrorMessage[0]);
		printf("%s\n", &fragmentShaderCubeErrorMessage[0]);
	}

	shader.program = glCreateProgram();
	glAttachShader(shader.program, shader.vertex);
	glAttachShader(shader.program, shader.fragment);
	glLinkProgram(shader.program);
	glGetProgramiv(shader.program, GL_LINK_STATUS, &shaderResult);
	glGetProgramiv(shader.program, GL_INFO_LOG_LENGTH, &shaderInfoLogLength);
	if (shaderInfoLogLength > 0)
	{
		std::vector<char> programCubeErrorMessage((unsigned int)(shaderInfoLogLength + 1));
		glGetProgramInfoLog(shader.program, shaderInfoLogLength, nullptr, &programCubeErrorMessage[0]);
		printf("%s\n", &programCubeErrorMessage[0]);
	}

	m_mShader.insert(std::make_pair(strTag, shader));
}

void (*m_pfMainLoop)(void*) = nullptr;

void RCGLSetMainLoopCallback(void (*mainLoop)(void*))
{
	m_pfMainLoop = mainLoop;
}

void RCGLMainLoop(GLFWwindow** ppWnd, void* pParam)
{
	while (!glfwWindowShouldClose(*ppWnd))
	{
		if (m_pfMainLoop)
			(*m_pfMainLoop)(pParam);

		glfwSwapBuffers(*ppWnd);
		glfwPollEvents();
	}
}

void RCGLSetVertexParam(const std::string& strTag, const std::string& strParamName, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	GLuint program = m_mShader[strTag].program;
	glUseProgram(program);
	glEnableVertexAttribArray((GLuint)glGetAttribLocation(program, strParamName.c_str()));
	glVertexAttribPointer((GLuint)glGetAttribLocation(program, strParamName.c_str()), size, type, normalized, stride, pointer);
}

void RCGLSetUniformMatrix4fv(const std::string& strTag, const std::string& strParamName, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	GLuint program = m_mShader[strTag].program;
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, strParamName.c_str()), count, transpose, value);
}

void RCGLSetUniform1i(const std::string& strTag, const std::string& strParamName, GLuint texTag, GLuint tex, GLuint layer)
{
	GLuint program = m_mShader[strTag].program;
	glUseProgram(program);
	glActiveTexture(texTag);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(glGetUniformLocation(program, strParamName.c_str()), layer);
}

void RCGLSetUniform4fv(const std::string& strTag, const std::string& strParamName, GLsizei count, const GLfloat* value)
{
	GLuint program = m_mShader[strTag].program;
	glUseProgram(program);
	glUniform4fv(glGetUniformLocation(program, strParamName.c_str()), count, value);
}

void RCGLDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
	glDrawElements(mode, count, type, indices);
}

void RCGLTerminate()
{
	glfwTerminate();
}