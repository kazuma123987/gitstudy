#include "main.h"

// N卡使用独显运行
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement;
__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
// main函数全局变量
static bool isShowCursor = true;
// 初始化类的static变量
GLuint FrameBuffer::VAO = 0;
GLuint FrameBuffer::VBO = 0;

int main(int argc, char *argv[])
{
	Game *game = new Game();
	if (game->init() == -1)
		fputs("\nfailed to init the game", stderr);
	// fmod
	s1 = InitSound();
	s2 = InitSound();
	music.init();
	music.loadMusic(s1, "res/music/start.mp3");
	FMOD_Sound_SetMode(s1->sound, FMOD_LOOP_NORMAL);
	music.loadMusic(s2, "res/music/choose.wav");
	music.playMusic(s1);
	// glEnable
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_MULTISAMPLE); // 开启多重采样缓冲(在不使用帧缓冲时不需要额外处理)
	// 绑定回调函数
	glfwSetFramebufferSizeCallback(window, frame_size_callback);
	glfwSetScrollCallback(window, scrollCallback);

	/*--------------------渲染循环--------------------*/
	while (!glfwWindowShouldClose(window))
	{
		//*INPUT
		press_close_window(window);
		mouse_button_input(window);
		keyboardInput(window);
		if (!isShowCursor)
		{
			camera->keyboardInput(window);
			camera->curseInput(window);
		}

		//*LOGIC
		camera->update();
		camera->updateUBO(); // 直接通过UBO把view和proj矩阵以全局变量(块)的形式发送
		game->update();

		//*Render
		// 渲染GUI界面
		game->rendGUI();
		/*------第一阶段处理(生成阴影贴图)------*/
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		game->rendShadowMap();

		/*------第二阶段处理(正常渲染)------*/
		game->rendGBuffer();
		game->deferredRend();
		// game->rendScene();

		/*------第三阶段处理(后期处理)------*/
		game->postRend();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		game->rendFPS(window); // 设置标题

		//* EVENTS && DISPLAY
		glfwSwapBuffers(window);
		glfwPollEvents(); // 处理窗口交互事件等
	}

	/*--------------------释放内存--------------------*/
	delete game;
	return 0;
}

void press_close_window(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, TRUE);
}

void frame_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyboardInput(GLFWwindow *window)
{
	static bool isPressP = false;
	static bool isPressN = false;
	if (!isPressP && glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		static bool f = FALSE;
		music.playMusic(s2);
		FMOD_Channel_SetPaused(s1->channel, (f = !f));
		isPressP = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		isPressP = false;
	if (!isPressN && glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		music.playMusic(s2);
		FMOD_Channel_Stop(s1->channel);
		isPressN = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		isPressN = false;
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