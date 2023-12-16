#ifndef _MAIN_H_
#define _MAIN_H_
#include <tool.h>
#include <global.h>
#include <sound.h>
#include <shader.h>
#include <mesh.h>
#include <model.h>
#include <frameBuffer.h>
// N卡使用独显运行
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
// main函数全局变量
GLFWwindow *window;
bool isShowCursor = true;
// 回调函数
void frame_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void keyboardInput(GLFWwindow *window)
{
	static bool isPressP=false;
	static bool isPressN=false;
	if (!isPressP&&glfwGetKey(window,GLFW_KEY_P)== GLFW_PRESS)
	{
		static bool f = FALSE;
		music.playMusic(s2);
		FMOD_Channel_SetPaused(s1->channel, (f = !f));
		isPressP=true;
	}
	else if (glfwGetKey(window,GLFW_KEY_P)== GLFW_PRESS)isPressP=false;
	if (!isPressN&&glfwGetKey(window,GLFW_KEY_N) == GLFW_PRESS)
	{
		music.playMusic(s2);
		FMOD_Channel_Stop(s1->channel);
		isPressN=true;
	}
	else if (glfwGetKey(window,GLFW_KEY_N)== GLFW_PRESS)isPressN=false;
}
void mouse_button_input(GLFWwindow *window)
{
	static bool isPress = false;
	if (!isPress && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		if (isShowCursor)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		isShowCursor = !isShowCursor;
		isPress = true;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		isPress = false;
}
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	if (!isShowCursor)
		camera->scrollCallback(yoffset);
}
// 普通函数
int gameInit()
{
	/*--------------文件路径初始化--------------*/
	GetModuleFileNameA(NULL, filePath, 260);
	char *c = strrchr(filePath, '\\');
	if (c != NULL)
		*(c + 1) = '\0';
	/*--------------glfw初始化--------------*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 注意设置的glfw上下文版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4); // 提示(Hint)glfw使用4个采样点的缓冲
#ifdef _APPLE_
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// 创建glfw窗口
	window = glfwCreateWindow(WIDTH, HEIGHT, "game", NULL, NULL);
	if (window == NULL)
	{
		fputs("\nfailed to create window", stderr);
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // 设置window为gl要处理的窗口环境
	glfwSwapInterval(0);
	/*--------------glad初始化--------------*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fputs("\nfailed to init glad", stderr);
		glfwTerminate();
		return -1;
	}
	/*--------------imgui初始化--------------*/
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiStyle &style=ImGui::GetStyle();
	style.WindowRounding=10.0f;
	style.FrameRounding=5.0f;
	style.WindowBorderSize=0.0f;
	ImGuiIO &io = ImGui::GetIO();
	SetCurrentDirectoryA(filePath);
	io.Fonts->AddFontFromFileTTF("res/fonts/yolan.ttf",18.0f,NULL,io.Fonts->GetGlyphRangesChineseFull());
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 400 core");
	return 0;
}
void press_close_window(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, TRUE);
}
void rendFPS(GLFWwindow *window)
{
	static int fps = 0;
	fps++;
	static auto preTime = std::chrono::high_resolution_clock::now();
	auto curTime = std::chrono::high_resolution_clock::now();
	if (std::chrono::duration_cast<std::chrono::milliseconds>(curTime - preTime).count() >= 1000)
	{
		preTime = curTime;
		std::string title = "game" + std::string("     ") + "FPS:" + std::to_string(fps);
		glfwSetWindowTitle(window, title.c_str());
		fps = 0;
	}
}
#endif