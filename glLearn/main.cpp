#include <main.h>
int main(int argc, char *argv[])
{
	Game *game=new Game();
	if (game->gameInit() == -1)
		fputs("\nfailed to init the game", stderr);
	/*--------------------音频设置--------------------*/
	// fmod
	s1 = InitSound();
	s2 = InitSound();
	music.init();
	music.loadMusic(s1, "res/music/start.mp3");
	FMOD_Sound_SetMode(s1->sound, FMOD_LOOP_NORMAL);
	music.loadMusic(s2, "res/music/choose.wav");
	music.playMusic(s1);
	// glEnable
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
		camera->update();
		camera->updateUBO(); //直接通过UBO把view和proj矩阵以全局变量(块)的形式发送
		
		//*LOGIC
		game->gameLogic();

		//*Rend
		//渲染GUI界面
		game->rendGUI();
		/*------第一阶段处理(生成阴影贴图)------*/
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		game->rendShadowMap();

		/*------第二阶段处理(正常渲染)------*/
		game->rendGBuffer();
		game->deferredRend();
		//game->rendScene();
		/*------第三阶段处理(后期处理)------*/			
		game->postRend();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// 设置标题
		rendFPS(window);

		//* EVENTS && DISPLAY
		glfwSwapBuffers(window);
		glfwPollEvents(); // 处理窗口交互事件等
	}

	/*--------------------释放内存--------------------*/
	delete game;
	return 0;
}