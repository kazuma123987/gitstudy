#include <tool.h>
#include <sound.h>
#include <shader.h>
#include <global.h>
#include <mesh.h>
#include <model.h>
#include <frameBuffer.h>
// N卡使用独显运行
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
// 不弹出调试控制台(用于Release版本)
// #pragma comment(linker, "/subsystem:\"windows\"  /entry:\"mainCRTStartup\"")
//  函数声明
void frame_size_callback(GLFWwindow *window, int width, int height);
void press_close_window(GLFWwindow *window);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
int main(int argc, char *argv[])
{
	// 获取文件当前路径
	// strcpy_s(filePath,"C:\\Users\\34181\\source\\repos\\glstudy\\glstudy");
	GetModuleFileNameA(NULL, filePath, 260);
	char *c = strrchr(filePath, '\\');
	if (c != NULL)
		*(c + 1) = '\0';
	// glfw初始化
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 注意设置的glfw上下文版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _APPLE_
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// 创建glfw窗口
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "game", NULL, NULL);
	if (window == NULL)
	{
		fputs("\nfailed to create window", stderr);
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // 设置window为gl要处理的窗口环境
	glfwSetFramebufferSizeCallback(window, frame_size_callback);
	// 使用glad加载opengl库
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fputs("\nfailed to init glad", stderr);
		glfwTerminate();
		return -1;
	}
	// 着色器
	SetCurrentDirectoryA(filePath);
	Shader cubeShader("shader\\cube.vert", "shader\\cube.frag","shader\\explode.geom");
	Shader lightShader("shader\\light.vert", "shader\\light.frag");
	Shader outlineShader("shader\\outline.vert", "shader\\outline.frag");
	Shader screenShader("shader\\screen.vert","shader\\screen.frag");
	Shader skyboxShader("shader\\skybox.vert","shader\\skybox.frag");
	//帧缓冲对象(FrameBuffer Object)
	FrameBuffer fbo(WIDTH,HEIGHT);
	/*--------------------模型参数设置--------------------*/
	// 创建或加载模型
	Mesh box(arr_vertex, arrVertex_N / 4, "res\\texture\\box1.png", "res\\texture\\box2.png");
	Mesh floor(arr_floor, arrFloor_N / 4, "res\\texture\\box4.png", "res\\texture\\box4.png");
	Mesh light(arr_vertex, arrVertex_N / 4, NULL, NULL);
	Mesh skybox(arr_vertex, arrVertex_N / 4,cubePaths);
	clock_t start = clock();
	Model human("C:\\Users\\34181\\Desktop\\code-demo\\gitstudy\\glLearn\\res\\3dmodels\\nanosuit_reflection\\nanosuit.blend");
	printf_s("load time:%dms", clock() - start);

	// 模型矩阵
	glm::mat4 boxMat[10];
	for (int i = 0; i < 10; i++)
	{
		boxMat[i] = glm::translate(glm::mat4(1.0f), offsetModel[i]);
		boxMat[i] = glm::rotate(boxMat[i], glm::radians(20.0f * i), glm::vec3(1.0f, i, i));
	}
	glm::mat4 humanMat = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
	// 光源矩阵
	glm::mat4 unitMat = glm::mat4(1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 2.0f, 3.0f);
	glm::vec3 lightColor[4] = {glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f)};
	// dirLight
	DirectLight dirLight = {glm::vec3(-0.1f, -1.0f, -0.1f), glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(0.5f)};
	// dotLight
	DotLight dotLight[4];
	glm::mat4 dotLightMat[4];
	for (int i = 0; i < 4; i++)
	{
		dotLight[i] = {lightPos + offsetModel[i], 0.02f * lightColor[i], 0.5f * lightColor[i], lightColor[i], 1.0f, 0.09f, 0.032f};
		dotLightMat[i] = glm::translate(unitMat, dotLight[i].pos);
	}
	// spotLight
	SpotLight spotLight = {glm::vec3(0.0f), glm::vec3(0.01f), glm::vec3(0.7f), glm::vec3(1.0f), 1.0f, 0.09f, 0.032f,
						   glm::cos(glm::radians(15.0f)), glm::cos(glm::radians(17.5f)), glm::vec3(0.0f, 0.0f, -1.0f)};
	/*--------------------音频设置--------------------*/
	// fmod
	s1 = InitSound();
	s2 = InitSound();
	music.init();
	music.loadMusic(s1, "res/music/start.mp3");
	FMOD_Sound_SetMode(s1->sound, FMOD_LOOP_NORMAL);
	music.loadMusic(s2, "res/music/choose.wav");
	music.playMusic(s1);

	// Camera
	camera = new Camera();
	// glEnable
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// 绑定回调函数
	glfwSetKeyCallback(window, keyCallback);
	glfwSetScrollCallback(window, scrollCallback);
	//先更新着色器块索引
	camera->setShaderUBOIndex(&cubeShader,"Mat");
	camera->setShaderUBOIndex(&lightShader,"Mat");
	camera->setShaderUBOIndex(&outlineShader,"Mat");
	camera->setShaderUBOIndex(&skyboxShader,"Mat");

	/*--------------------渲染循环--------------------*/
	while (!glfwWindowShouldClose(window))
	{
		// INPUT
		press_close_window(window);
		camera->keyboardInput(window);
		camera->curseInput(window);

		/*------第一阶段处理------*/
		fbo.bind();
		// LOGIC && RENDER
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glStencilMask(0x00);
		float t = glfwGetTime();
		camera->update();
		camera->updateUBO();//直接通过UBO把view和proj矩阵以全局变量(块)的形式发送
		// LIGHT(先渲染光源,因为后续物体受光源影响)
		lightShader.use();
		// dotLight//
		lightPos.x = 3 * sin(t);
		lightPos.z = 3 * cos(t);
		for (int i = 0; i < 4; i++)
		{
			lightColor[i] = {sin(0.2f * t + 2 * i) * 0.5f + 0.5f, sin(0.5f * t + 2 * i) * 0.5f + 0.5f, sin(0.7f * t + 2 * i) * 0.5f + 0.5f};
			lightShader.unfvec3fv("lightColor", lightColor[i]);
			dotLight[i] = {lightPos + offsetModel[i], 0.1f * lightColor[i], 0.5f * lightColor[i], lightColor[i], 1.0f, 0.09f, 0.032f};
			dotLightMat[i] = glm::scale(glm::translate(unitMat, dotLight[i].pos), glm::vec3(0.2f));
			lightShader.unfmat4fv("model", dotLightMat[i]);
			light.Draw(&lightShader);
		}
		// spotLight//
		spotLight.pos = camera->getCameraPos();
		spotLight.front = camera->getCameraFront();
		// model
		cubeShader.use();
		cubeShader.unfm1f("time",abs(t/2.0f-(int)(t/2.0f)-0.5f)*2.0f);
		cubeShader.unfm1i("texture_cube1",4);//设置要传入GL_TEXTURE4
		glActiveTexture(GL_TEXTURE4);		//激活纹理单元4
		glBindTexture(GL_TEXTURE_CUBE_MAP,skybox.textures[0].id);//把立方体纹理绑定到当前纹理单元
		cubeShader.unfDirLight("dirLight", &dirLight);
		for (int i = 0; i < 4; i++)
			cubeShader.unfDotLight((std::string("dotLight") + "[" + std::to_string(i) + "]").c_str(), &dotLight[i]);
		cubeShader.unfSpotLight("spotLight", &spotLight);
		cubeShader.unfvec3fv("viewerPos", camera->getCameraPos());
		cubeShader.unfm1f("material.shininess", 32.0f);
		// 绘制箱子
		glEnable(GL_CULL_FACE);//允许面剔除
		glCullFace(GL_BACK);//剔除背面（默认就是GL_BACK）
		glFrontFace(GL_CCW);//将逆时针的面定义为正面,GL_CW则反之（默认就是GL_CCW）
		glm::mat3 normMat;
		for (int i = 0; i < 10; i++)
		{
			cubeShader.unfmat4fv("model", boxMat[i]);
			normMat = glm::mat3(glm::transpose(glm::inverse(boxMat[i])));
			cubeShader.unfmat3fv("normMat", normMat);
			box.Draw(&cubeShader);
		}
		glDisable(GL_CULL_FACE);
		// 绘制地面
		cubeShader.unfmat4fv("model", unitMat);
		normMat = glm::mat3(glm::transpose(glm::inverse(unitMat)));
		cubeShader.unfmat3fv("normMat", normMat);
		floor.Draw(&cubeShader);
		// 绘制人物
		glEnable(GL_CULL_FACE);
		glStencilFunc(GL_ALWAYS,1,0xff);
		glStencilMask(0xff);
		normMat = glm::mat3(glm::transpose(glm::inverse(humanMat)));
		cubeShader.unfmat3fv("normMat", normMat);
		cubeShader.unfmat4fv("model", humanMat);
		human.Draw(&cubeShader);
		glDisable(GL_CULL_FACE);//人物2的发带只有单面,不能用面剔除
		//绘制天空盒
		glDepthFunc(GL_LEQUAL);
		skyboxShader.use();
		skybox.Draw(&skyboxShader);
		glDepthFunc(GL_LESS);

		/*------第二阶段处理(后期处理)------*/
		fbo.Draw(&screenShader);

		// SOUND
		music.set3DPosition(s1, sin(t), cos(t), 0);
		music.updateSystem();

		// EVENTS && DISPLAY
		glfwSwapBuffers(window);
		glfwPollEvents(); // 处理窗口交互事件等
	}

	/*--------------------释放内存--------------------*/
	glfwTerminate(); // 不要忘记释放glfw资源
	fbo.destoyFBO();
	deleteSound(s1);
	deleteSound(s2);
	delete (camera);
	music.systemFree();
	return 0;
}
// 回调函数
void frame_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == (GLFW_KEY_P) && action == GLFW_PRESS)
	{
		static bool f = FALSE;
		music.playMusic(s2);
		FMOD_Channel_SetPaused(s1->channel, (f = !f));
	}
	else if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		music.playMusic(s2);
		FMOD_Channel_Stop(s1->channel);
	}
}
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	camera->scrollCallback(yoffset);
}
// 普通函数
void press_close_window(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, TRUE);
}