#include "tool.h"
#include "sound.h"
#include "shader.h"
#include "global.h"
// N卡使用独显运行
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
//不弹出调试控制台(用于Release版本)
//#pragma comment(linker, "/subsystem:\"windows\"  /entry:\"mainCRTStartup\"")
// 函数声明
void frame_size_callback(GLFWwindow* window, int width, int height);
void press_close_window(GLFWwindow* window);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
int main(int argc, char* argv[])
{
	// 获取文件当前路径
   // strcpy_s(filePath,"C:\\Users\\34181\\source\\repos\\glstudy\\glstudy");
	GetModuleFileNameA(NULL, filePath, 260);
	// char* c = strrchr(filePath, '\\');
	// if (c != NULL)
	//     *(c + 1) = '\0';
	 // glfw初始化
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 注意设置的glfw上下文版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _APPLE_
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// 创建glfw窗口
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "game", NULL, NULL);
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

	// VAO
	GLuint modelVAO;
	GLuint lightVAO;
	glGenVertexArrays(1, &modelVAO);
	glGenVertexArrays(1, &lightVAO);

	// VBO
	GLuint modelVBO;
	glGenBuffers(1, &modelVBO);
	glBindBuffer(GL_ARRAY_BUFFER, modelVBO);
	glBufferData(GL_ARRAY_BUFFER, arrVertex_N, arr_vertex, GL_STATIC_DRAW);
	// VAO的顶点指针属性设置(先发送数据到显存,再绑定VAO，再设置顶点指针)
	glBindVertexArray(modelVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // 顶点坐标
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // 纹理坐标
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float))); // 法向量坐标
	glEnableVertexAttribArray(2);

	glBindVertexArray(lightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // 顶点坐标
	glEnableVertexAttribArray(0);

	// 创建着色器程序
	SetCurrentDirectoryA(filePath);
	Shader modelShader("res\\shader\\model.vert", "res\\shader\\model.frag");
	Shader lightShader("res/shader/model.vert", "res/shader/light.frag");

	/*--------------------TEXTURE--------------------*/
	GLuint texture[6];//6个纹理
	glGenTextures(6, texture);
	int width[6], height[6], nColorChannels[6];//纹理的宽、高、颜色通道数
	stbi_set_flip_vertically_on_load(TRUE);//开启竖直翻转
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//设置纹理为单字节传输
	for (int i = 0; i < 6; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texture[i]); // 绑定第一个纹理
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // 只有缩小能开启多级渐远纹理
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// 加载并发送纹理
		char* imagePath = (char*)calloc(20, sizeof(char));//图片路径
		if (imagePath)
			sprintf_s(imagePath, 20, "res/texture/%d.jpg", i + 1);//str的长度应大于等于目标字符串长度+1
		else
			fputs("calloc failed", stderr);

		unsigned char* imageData = stbi_load(imagePath, &width[i], &height[i], &nColorChannels[i], 0);
		if (imageData)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width[i], height[i], 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
			fputs("\nfailed to load the image", stderr);
		stbi_image_free(imageData); // 纹理已加载，删除纹理数组
		free(imagePath);//清除图片路径缓冲区
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);//恢复纹理单行4字节传输
	// 指定纹理单元传入的位置
	modelShader.use();
	modelShader.unfm1i("ourTexture[0]", 0);
	modelShader.unfm1i("ourTexture[1]", 1);
	modelShader.unfm1i("ourTexture[2]", 2);
	modelShader.unfm1i("ourTexture[3]", 3);
	modelShader.unfm1i("ourTexture[4]", 4);
	modelShader.unfm1i("ourTexture[5]", 5);
	// 绑定纹理
	for (int i = 0; i < 6; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texture[i]);
	}

	/*--------------------其他参数设置--------------------*/
	// fmod
	s1 = InitSound();
	s2 = InitSound();
	music.init();
	music.loadMusic(s1, "res/music/start.mp3");
	FMOD_Sound_SetMode(s1->sound, FMOD_LOOP_NORMAL);
	music.loadMusic(s2, "res/music/choose.wav");
	music.playMusic(s1);
	//模型矩阵
	glm::mat4 model[10];
	for (int i = 0; i < 10; i++)
	{
		model[i] = glm::translate(glm::mat4(1.0f), offsetModel[i]);
		model[i] = glm::rotate(model[i], glm::radians(20.0f * i), glm::vec3(1.0f, i, i));
	}
	//光源矩阵
	glm::mat4 unitMat = glm::mat4(1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.8f, 3.0f);
	glm::vec3 lightColor = glm::vec3(1.0f);
	//Camera
	camera = new Camera();
	//glEnable
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//绑定回调函数
	glfwSetKeyCallback(window, keyCallback);
	glfwSetScrollCallback(window, scrollCallback);

	/*--------------------渲染循环--------------------*/
	while (!glfwWindowShouldClose(window))
	{
		// INPUT
		press_close_window(window);
		camera->keyboardInput(window);
		camera->curseInput(window);

		// LOGIC && RENDER
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float t = 2 * glfwGetTime();
		lightPos.z = sin(t);
		lightPos.x = cos(t);
		//model
		modelShader.use();
		camera->update();
		camera->updateMat(modelShader);
		glBindVertexArray(modelVAO);
		modelShader.unfvec3fv("lightColor", lightColor);
		modelShader.unfvec3fv("LightPos", lightPos);
		for (int i = 0; i < 1; i++)
		{
			modelShader.unfmat4fv("model", model[i]);
			glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(camera->getViewMat() * model[i])));
			modelShader.unfmat3fv("normalMat", normalMat);
			for (int j = 0; j < 6; j++)
			{
				modelShader.unfm1i("texIndex", j);
				glDrawArrays(GL_TRIANGLES, j * 6, 6);
			}
		}
		//light
		glBindVertexArray(lightVAO);
		lightShader.use();
		glm::mat4 lightMat = glm::translate(unitMat, lightPos);
		lightMat = glm::scale(lightMat, glm::vec3(0.2f, 0.2f, 0.2f));//先位移再进行缩放或者旋转
		lightShader.unfmat4fv("model", lightMat);
		lightShader.unfvec3fv("lightColor", lightColor);
		camera->updateMat(lightShader);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// SOUND
		music.set3DPosition(s1, sin(t), cos(t), 0);
		music.updateSystem();

		// EVENTS && DISPLAY
		glfwSwapBuffers(window);
		glfwPollEvents();//处理窗口交互事件等
	}

	/*--------------------释放内存--------------------*/
	glDeleteVertexArrays(1, &modelVAO); // 删除VAO绑定的一个VAO对象
	glDeleteBuffers(1, &modelVBO);      // 删除VBO绑定的一个缓存对象
	glDeleteTextures(6, texture);
	glfwTerminate(); // 不要忘记释放glfw资源
	deleteSound(s1);
	deleteSound(s2);
	delete(camera);
	music.systemFree();
	return 0;
}
// 回调函数
void frame_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
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
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->scrollCallback(yoffset);
}
// 普通函数
void press_close_window(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, TRUE);
}