#include <cstdio>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GameLogic/Cube.h>
#include <Base/GLBasic.h>
#include <Base/RCButton.h>

using namespace glm;

int WND_WIDTH = 800;
int WND_HEIGHT = 600;
#define WND_TITLE "Rubik's Cube"

Cube* cube;

glm::mat4 projection;
glm::mat4 view;
glm::mat4 model;

RCButton* btnRed = nullptr;
RCButton* btnGreen = nullptr;
RCButton* btnYellow = nullptr;
RCButton* btnOrange = nullptr;
RCButton* btnBlue = nullptr;
RCButton* btnWhite = nullptr;
RCButton* btnExit = nullptr;
RCButton* btnTips = nullptr;
RCButton* btnDisrupt = nullptr;

#define OnKeyEventPress(wnd, key) \
state = glfwGetKey(wnd, key); \
if (state == GLFW_PRESS)

void keyboardEvent(GLFWwindow* pWnd)
{
	int state;
	OnKeyEventPress(pWnd, GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(pWnd, GLFW_TRUE);
		return;
	}
	OnKeyEventPress(pWnd, GLFW_KEY_A)
	{
		model = glm::rotate(model, -glm::pi<float>() / 48, glm::vec3(0.0f, 1.0f, 0.0f));
		return;
	}
	OnKeyEventPress(pWnd, GLFW_KEY_D)
	{
		model = glm::rotate(model, glm::pi<float>() / 48, glm::vec3(0.0f, 1.0f, 0.0f));
		return;
	}
	OnKeyEventPress(pWnd, GLFW_KEY_W)
	{
		model = glm::rotate(model, -glm::pi<float>() / 48, glm::vec3(1.0f, 0.0f, 0.0f));
		return;
	}
	OnKeyEventPress(pWnd, GLFW_KEY_S)
	{
		model = glm::rotate(model, glm::pi<float>() / 48, glm::vec3(1.0f, 0.0f, 0.0f));
		return;
	}
	OnKeyEventPress(pWnd, GLFW_KEY_Q)
	{
		model = glm::rotate(model, -glm::pi<float>() / 48, glm::vec3(0.0f, 0.0f, 1.0f));
		return;
	}
	OnKeyEventPress(pWnd, GLFW_KEY_E)
	{
		model = glm::rotate(model, glm::pi<float>() / 48, glm::vec3(0.0f, 0.0f, 1.0f));
		return;
	}
}

#define OnButtonDown(btn, x, y) \
if (x >= btn->GetXPos() && y <= btn->GetYPos()) \
	if (x <= btn->GetXPos() + btn->GetWidth() * 2.0f / WND_WIDTH && y >= btn->GetYPos() - btn->GetHeight() * 2.0f / WND_HEIGHT)

#define OnButtonLeftPart(btn, x, y) \
if (x >= btn->GetXPos() && y <= btn->GetYPos()) \
	if (x <= btn->GetXPos() + btn->GetWidth() / float(WND_WIDTH) && y >= btn->GetYPos() - btn->GetHeight() * 2.0f / WND_HEIGHT)

#define OnButtonRightPart(btn, x, y) \
if (x >= btn->GetXPos() + btn->GetWidth() / float(WND_WIDTH) && y <= btn->GetYPos()) \
	if (x <= btn->GetXPos() + btn->GetWidth() * 2.0f / WND_WIDTH && y >= btn->GetYPos() - btn->GetHeight() * 2.0f / WND_HEIGHT)

void mouseCallback(GLFWwindow* pWnd, int button, int action, int mods)
{
	double x, y;
	glfwGetCursorPos(pWnd, &x, &y);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		glm::vec3 vPos = { x, y, 1 };
		glm::mat3 matCnv;
		matCnv[0][0] = 2.0f / WND_WIDTH; matCnv[1][0] = 0; matCnv[2][0] = -1;
		matCnv[0][1] = 0; matCnv[1][1] = -2.0f / WND_HEIGHT; matCnv[2][1] = 1;
		matCnv[0][2] = 0; matCnv[1][2] = 0; matCnv[2][2] = 1;
		glm::vec3 scrCoord = matCnv * vPos;
		OnButtonDown(btnExit, scrCoord.x, scrCoord.y)
			{
				glfwSetWindowShouldClose(pWnd, GLFW_TRUE);
				return;
			}
		OnButtonDown(btnDisrupt, scrCoord.x, scrCoord.y)
			{
				cube->Disrupt();
				return;
			}
		OnButtonLeftPart(btnRed, scrCoord.x, scrCoord.y)
			{
				cube->RotateRedCW();
				return;
			}
		OnButtonRightPart(btnRed, scrCoord.x, scrCoord.y)
			{
				cube->RotateRedCCW();
				return;
			}
		OnButtonLeftPart(btnGreen, scrCoord.x, scrCoord.y)
			{
				cube->RotateGreenCW();
				return;
			}
		OnButtonRightPart(btnGreen, scrCoord.x, scrCoord.y)
			{
				cube->RotateGreenCCW();
				return;
			}
		OnButtonLeftPart(btnYellow, scrCoord.x, scrCoord.y)
			{
				cube->RotateYellowCW();
				return;
			}
		OnButtonRightPart(btnYellow, scrCoord.x, scrCoord.y)
			{
				cube->RotateYellowCCW();
				return;
			}
		OnButtonLeftPart(btnOrange, scrCoord.x, scrCoord.y)
			{
				cube->RotateOrangeCW();
				return;
			}
		OnButtonRightPart(btnOrange, scrCoord.x, scrCoord.y)
			{
				cube->RotateOrangeCCW();
				return;
			}
		OnButtonLeftPart(btnBlue, scrCoord.x, scrCoord.y)
			{
				cube->RotateBlueCW();
				return;
			}
		OnButtonRightPart(btnBlue, scrCoord.x, scrCoord.y)
			{
				cube->RotateBlueCCW();
				return;
			}
		OnButtonLeftPart(btnWhite, scrCoord.x, scrCoord.y)
			{
				cube->RotateWhiteCW();
				return;
			}
		OnButtonRightPart(btnWhite, scrCoord.x, scrCoord.y)
			{
				cube->RotateWhiteCCW();
				return;
			}
		return;
	}
}

struct MainLoopParam
{
	GLFWwindow* pWnd;
};

void renderButton(RCButton* pBtn, GLfloat* colorBack, GLfloat* colorText)
{
	auto vTri = pBtn->GetTriangles(WND_WIDTH, WND_HEIGHT);
	RCGLSetVertexParam("button", "positionInput", 2, GL_FLOAT, GL_FALSE, 0, &vTri[0]);
	auto vTexCoord = pBtn->GetTexcoords();
	RCGLSetVertexParam("button", "texcoordInput", 2, GL_FLOAT, GL_FALSE, 0, &vTexCoord[0]);
	RCGLSetUniform1i("button", "texInput", GL_TEXTURE0, pBtn->GetTexture(), 0);
	RCGLSetUniform4fv("button", "colorBack", 1, colorBack);
	RCGLSetUniform4fv("button", "colorText", 1, colorText);
	auto vId = pBtn->GetIndices();
	RCGLDrawElements(GL_TRIANGLES, vId.size(), GL_UNSIGNED_INT, (void*)&vId[0]);
}

void mainLoop(void* pParam)
{
	auto pMLP = (MainLoopParam*)pParam;

	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glm::mat4 mvp = projection * view * model; // Remember, matrix multiplication is the other way around

	glEnable(GL_DEPTH_TEST);
	auto vCubeTri = cube->GetTriangles();
	RCGLSetVertexParam("cube", "positionInput", 4, GL_FLOAT, GL_FALSE, 0, &vCubeTri[0]);
	auto vCubeColor = cube->GetColors();
	RCGLSetVertexParam("cube", "colorInput", 4, GL_FLOAT, GL_FALSE, 0, &vCubeColor[0]);
	auto vCubeCenter = cube->GetCenters();
	RCGLSetVertexParam("cube", "centerInput", 4, GL_FLOAT, GL_FALSE, 0, &vCubeCenter[0]);
	RCGLSetUniformMatrix4fv("cube", "mvp", 1, GL_FALSE, &mvp[0][0]);
	auto vCubeIndices = cube->GetIndices();
	RCGLDrawElements(GL_TRIANGLES, vCubeIndices.size(), GL_UNSIGNED_INT, (void*)&vCubeIndices[0]);

	glDisable(GL_DEPTH_TEST);
	GLfloat whiteText[] = { 1, 1, 1, 1 };
	GLfloat blackText[] = { 0, 0, 0, 1 };
	GLfloat colorBackBtnExit[] = { 0.618, 0, 0.382, 1 };
	renderButton(btnExit, colorBackBtnExit, whiteText);
	GLfloat colorRed[] = { 0.835294f, 0, 0.062745f, 1 };
	renderButton(btnRed, colorRed, whiteText);
	GLfloat colorGreen[] = { 0, 0.623529f, 0.074510f, 1 };
	renderButton(btnGreen, colorGreen, whiteText);
	GLfloat colorYellow[] = { 1, 1, 0, 1 };
	renderButton(btnYellow, colorYellow, blackText);
	GLfloat colorOrange[] = { 0.996078f, 0.541176f, 0.039216f, 1 };
	renderButton(btnOrange, colorOrange, whiteText);
	GLfloat colorBlue[] = { 0, 0.274510f, 0.623529f, 1 };
	renderButton(btnBlue, colorBlue, whiteText);
	GLfloat colorWhite[] = { 1, 1, 1, 1 };
	renderButton(btnWhite, colorWhite, blackText);

	renderButton(btnTips, blackText, whiteText);
	GLfloat colorDisrupt[] = { 0, 0.618f, 0, 1 };
	renderButton(btnDisrupt, colorDisrupt, whiteText);

	keyboardEvent(pMLP->pWnd);
}

int main()
{
	// cube initialize
	cube = new Cube;
	// OpenGL Initialize
	GLFWwindow* pWnd;
	RCGLInitialize(&pWnd, WND_WIDTH, WND_HEIGHT, WND_TITLE);
	RCGLSetMouseButtonCallback(&pWnd, mouseCallback);
	RCGLSetMainLoopCallback(mainLoop);
	// load shader
	RCGLLoadShader("cube", "cube.vs", "cube.fs");
	RCGLLoadShader("button", "button.vs", "button.fs");
	// buttons
	float fYPosOffset = 1;
	btnRed = new RCButton("mingliu.ttc", 32, 32, -1, fYPosOffset, L"[順時針][逆時針]");
	fYPosOffset -= btnRed->GetHeight() * 2.0f / WND_HEIGHT;
	btnGreen = new RCButton("mingliu.ttc", 32, 32, -1, fYPosOffset, L"[順時針][逆時針]");
	fYPosOffset -= btnGreen->GetHeight() * 2.0f / WND_HEIGHT;
	btnYellow = new RCButton("mingliu.ttc", 32, 32, -1, fYPosOffset, L"[順時針][逆時針]");

	fYPosOffset = 1;
	btnOrange = new RCButton("mingliu.ttc", 32, 32, 1, fYPosOffset, L"[順時針][逆時針]");
	btnOrange->SetXPos(1 - btnOrange->GetWidth() * 2.0f / WND_WIDTH);
	fYPosOffset -= btnOrange->GetHeight() * 2.0f / WND_HEIGHT;
	btnBlue = new RCButton("mingliu.ttc", 32, 32, 1, fYPosOffset, L"[順時針][逆時針]");
	btnBlue->SetXPos(1 - btnBlue->GetWidth() * 2.0f / WND_WIDTH);
	fYPosOffset -= btnBlue->GetHeight() * 2.0f / WND_HEIGHT;
	btnWhite = new RCButton("mingliu.ttc", 32, 32, 1, fYPosOffset, L"[順時針][逆時針]");
	btnWhite->SetXPos(1 - btnWhite->GetWidth() * 2.0f / WND_WIDTH);

	btnExit = new RCButton("mingliu.ttc", 32, 32, 1, -1, L"退出");
	btnExit->SetXPos(1 - btnExit->GetWidth() * 2.0f / WND_WIDTH);
	btnExit->SetYPos(-1 + btnExit->GetHeight() * 2.0f / WND_HEIGHT);

	btnDisrupt = new RCButton("mingliu.ttc", 32, 32, 1, -1, L"打亂");
	btnDisrupt->SetXPos(1 - btnDisrupt->GetWidth() * 2.0f / WND_WIDTH);
	btnDisrupt->SetYPos(-1 + (btnExit->GetHeight() + btnDisrupt->GetHeight()) * 2.0f / WND_HEIGHT);

	btnTips = new RCButton("mingliu.ttc", 24, 24, -1, -1, L"按下W/S、A/D、Q/E調整角度，點擊對應的按鈕進行相關操作。");
	btnTips->SetYPos(-1 + btnTips->GetHeight() * 2.0f / WND_HEIGHT);
	// camera matrix initialize
	projection = glm::perspective(glm::radians(45.0f), float(WND_WIDTH) / WND_HEIGHT, 0.000001f, 100.0f);
	view = glm::lookAt(
			glm::vec3(6, 6, 6), // Camera is at (x, y, z), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0, -1, 0 to look upside-down)
	);
	model = glm::mat4(1.0f);
	// use shaders
	std::vector<v4> triangles = cube->GetTriangles();
	std::vector<v4> colors = cube->GetColors();
	std::vector<v4> centers = cube->GetCenters();
	std::vector<unsigned int> indices = cube->GetIndices();
	// main loop
	MainLoopParam param = {
			pWnd,
	};
	RCGLMainLoop(&pWnd, &param);
	// terminate
	RCGLTerminate();
	delete btnRed; btnRed = nullptr;
	delete btnGreen; btnGreen = nullptr;
	delete btnYellow; btnYellow = nullptr;
	delete btnOrange; btnOrange = nullptr;
	delete btnBlue; btnBlue = nullptr;
	delete btnWhite; btnWhite = nullptr;
	delete btnExit; btnExit = nullptr;
	delete btnTips; btnTips = nullptr;
	delete btnDisrupt; btnDisrupt = nullptr;
	delete cube; cube = nullptr;
	return 0;
}