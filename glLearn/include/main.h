#ifndef _MAIN_H_
#define _MAIN_H_
#include <tool.h>
#include <global.h>
#include <sound.h>
#include <shader.h>
#include <mesh.h>
#include <model.h>
#include <frameBuffer.h>
#include <fonts.h>
// N卡使用独显运行
extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
// main函数全局变量
GLFWwindow *window;
bool isShowCursor = true;
Camera *camera;
GLuint FrameBuffer::VAO = 0;
GLuint FrameBuffer::VBO = 0;
glm::vec3 getPoint(GLfloat u, GLfloat v)
{
	GLfloat r = 90.0f;
	GLfloat pi = glm::pi<GLfloat>();
	GLfloat z = r * std::cos(pi * u);
	GLfloat x = r * std::sin(pi * u) * std::cos(2 * pi * v);
	GLfloat y = r * std::sin(pi * u) * std::sin(2 * pi * v);
	// std::cout << x << "," << y << "," << z << std::endl;
	return glm::vec3(x, y, z);
}
void createSphere(GLfloat *sphere, GLuint Longitude, GLuint Latitude)
{
	// Longitude：经线切分个数
	// Latitude：纬线切分个数
	GLfloat lon_step = 1.0f / Longitude;
	GLfloat lat_step = 1.0f / Latitude;
	GLuint offset = 0;
	for (int lat = 0; lat < Latitude; lat++)
	{ // 纬线u
		for (int lon = 0; lon < Longitude; lon++)
		{ // 经线v
			// 一次构造4个点，两个三角形，
			glm::vec2 uv1(lat * lat_step, lon * lon_step);
			glm::vec2 uv2((lat + 1) * lat_step, lon * lon_step);
			glm::vec2 uv3((lat + 1) * lat_step, (lon + 1) * lon_step);
			glm::vec2 uv4(lat * lat_step, (lon + 1) * lon_step);
			glm::vec3 point1 = getPoint(uv1.x, uv1.y);
			glm::vec3 point2 = getPoint(uv2.x, uv2.y);
			glm::vec3 point3 = getPoint(uv3.x, uv3.y);
			glm::vec3 point4 = getPoint(uv4.x, uv4.y);
			memcpy(sphere + offset, glm::value_ptr(point1), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(sphere + offset, glm::value_ptr(uv1), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(sphere + offset, glm::value_ptr(point4), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(sphere + offset, glm::value_ptr(uv4), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(sphere + offset, glm::value_ptr(point3), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(sphere + offset, glm::value_ptr(uv3), 2 * sizeof(GLfloat));
			offset += 2;

			memcpy(sphere + offset, glm::value_ptr(point1), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(sphere + offset, glm::value_ptr(uv1), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(sphere + offset, glm::value_ptr(point3), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(sphere + offset, glm::value_ptr(uv3), 2 * sizeof(GLfloat));
			offset += 2;
			memcpy(sphere + offset, glm::value_ptr(point2), 3 * sizeof(GLfloat));
			offset += 3;
			memcpy(sphere + offset, glm::value_ptr(uv2), 2 * sizeof(GLfloat));
			offset += 2;
		}
	}
	// std::cout<<"offset:" << offset << std::endl;
}
void utf8_to_wchar(wchar_t *dst, size_t dstlen, char *src)
{
	size_t len = strlen(src);
	size_t w_size = MultiByteToWideChar(CP_UTF8, 0, src, len, NULL, 0);
	if (w_size > dstlen)
	{
		printf("\nutf8_to_wchar error::out of the dst buffer");
		return;
	}
	MultiByteToWideChar(CP_UTF8, 0, src, len, dst, w_size);
	dst[w_size] = L'\0';
};
void press_close_window(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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
class Game
{
public:
	// 用于四边形(quad)绘制的VAO/VBO
	GLuint quadVAO = 0;
	GLuint quadVBO;
	GLuint noiseMap;
	std::vector<glm::vec3> ssaoSamples;
	Fonts *font;
	// GUI变量
	bool drawRock = true;
	bool skyBox_ON = false;
	bool dirLight_ON = true;
	bool dotLight_ON = true;
	bool spotLight_ON = false;
	bool ssao_ON = false;
	float height_scale = 0.1f;
	int blurCount = 1;
	int kernelSize = 64;
	float kernelRadius = 0.5f;
	char textBuffer[4096] = {'I', 'n', 'p', 'u', 't', 'T', 'e', 'x', 't', '\0'};
	wchar_t wtestBuffer[4096] = {0};
	float textScale = 1.0f;
	float text_thickness = 0.5f;
	float text_softness = 0.0f;
	float outline_thickness = 0.5f;
	float outline_softness = 0.0f;
	glm::vec3 textColor = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 outlineColor = glm::vec3(1.0f);
	// 着色器
	Shader *cubeShader;
	Shader *modelShader;
	Shader *lightShader;
	Shader *outlineShader;
	Shader *screenShader;
	Shader *skyboxShader;
	Shader *instantShader;
	Shader *depthShader;
	Shader *depthCubeShader;
	Shader *blurShader;
	Shader *twoTexShader;
	Shader *gBufferShader;
	Shader *deferredShader;
	Shader *ssaoShader;
	Shader *simpleBlurShader;
	Shader *fontShader;
	Shader *ballShader;
	// 模型和网格
	Mesh *box;
	Mesh *wall;
	Mesh *redWall;
	Mesh *toyBox;
	Mesh *ground;
	Mesh *light;
	Mesh *skybox;
	Model *human;
	Model *rock;
	Mesh *sphere;
	const int rockNum = 100000;
	glm::mat4 boxMat[10];
	glm::mat4 humanMat = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
	glm::mat4 *rockMat;
	const float near_plane = 0.1f;
	const float far_plane = 100.0f;
	// 光源矩阵
	glm::mat4 unitMat = glm::mat4(1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 4.0f, 3.0f);
	// dirLight
	DirectLight dirLight = {glm::vec3(2.0f, -8.0f, 1.0f), glm::vec3(0.1f), glm::vec3(0.1f), glm::vec3(0.01f)};
	glm::mat4 dirShadowSpaceMat = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane) * glm::lookAt(-dirLight.dir, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// dotLight
	glm::vec3 dotColor = glm::vec3(1.0f);
	DotLight dotLight = {lightPos, 0.02f * dotColor, 0.5f * dotColor, dotColor, 1.0f, 0.09f, 0.032f};
	glm::mat4 dotLightMat = glm::translate(unitMat, dotLight.pos);
	glm::mat4 dotShadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
	glm::mat4 dotShadowMat[6];
	// spotLight
	glm::vec3 spotColor = glm::vec3(1.0f);
	SpotLight spotLight = {glm::vec3(0.0f), glm::vec3(0.01f), glm::vec3(0.7f), glm::vec3(1.0f), 1.0f, 0.09f, 0.032f,
						   glm::cos(glm::radians(15.0f)), glm::cos(glm::radians(17.5f)), glm::vec3(0.0f, 0.0f, -1.0f)};
	glm::mat4 spotShadowSpaceMat;
	// 帧缓冲对象（当纹理预分配空间(imageData=NULL)且绑定对象不存在时纹理的缓冲区也会随之消失
	// 例如声明全局变量FrameBuffer a,b;令FrameBuffer test(WIDTH,HEIGHT);a=test;则a拷贝过来的纹理缓冲会在test生命结束时被释放
	// 同时若a=FrameBuffer(WIDTH,HEIGHT);n=FrameBuffer(WIDTH,HEIGHT);则a和b的纹理缓冲始终是同一个
	// 因为纹理缓冲的分配规则:若当前最新纹理缓冲有数据,则不论绑定对象是否存在,都可以通过ID查找,分配新纹理时默认ID为当前最新ID+1
	// 若当前最新纹理缓冲没有数据,只要绑定对象存在,就不会主动释放内存,若绑定对象不存在,则会主动释放内存,分配的新纹理ID与对象作用域有关
	FrameBuffer *finalFBO;
	FrameBuffer *texFBO;
	FrameBuffer *twoTexFBO;
	FrameBuffer *pingpongFBO;
	FrameBuffer *shadowFBO;
	FrameBuffer *spotShadowFBO;
	FrameBuffer *gBufferFBO;
	FrameBuffer *ssaoFBO;
	FrameBuffer *ssaoBlurFBO;
	Game(){};
	~Game()
	{
		game_free();
	};
	int gameInit()
	{
		// 设置纹理y轴(V轴)翻转
		stbi_set_flip_vertically_on_load(true);
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
		ImGuiStyle &style = ImGui::GetStyle();
		style.WindowRounding = 10.0f;
		style.FrameRounding = 5.0f;
		style.WindowBorderSize = 0.0f;
		ImGuiIO &io = ImGui::GetIO();
		SetCurrentDirectoryA(filePath);
		io.Fonts->AddFontFromFileTTF("res/fonts/yolan.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 400 core");
		/*--------------全局变量初始化--------------*/
		valueInit();
		return 0;
	}
	void valueInit()
	{
		// Camera
		camera = new Camera();
		// Font
		SetCurrentDirectoryA(filePath);
		std::vector<std::string> path = {"res/fonts/yolan.ttf"};
		font = new Fonts(path);
		font->loadChars();
		// 着色器
		cubeShader = new Shader("cubeShader", "shader\\objectsShader\\cube.vert", "shader\\objectsShader\\cube.frag");
		modelShader = new Shader("modelShader", "shader\\objectsShader\\model.vert", "shader\\objectsShader\\model.frag");
		lightShader = new Shader("lightShader", "shader\\objectsShader\\light.vert", "shader\\objectsShader\\light.frag");
		outlineShader = new Shader("outlineShader", "shader\\specialShader\\outline.vert", "shader\\specialShader\\outline.frag");
		screenShader = new Shader("screenShader", "shader\\postShader\\screen.vert", "shader\\postShader\\screen.frag");
		skyboxShader = new Shader("skyboxShader", "shader\\specialShader\\skybox.vert", "shader\\specialShader\\skybox.frag");
		instantShader = new Shader("instantShader", "shader\\objectsShader\\instant.vert", "shader\\objectsShader\\instant.frag");
		depthShader = new Shader("depthShader", "shader\\shadowShader\\depthMap.vert", "shader\\shadowShader\\depthMap.frag");
		depthCubeShader = new Shader("depthCubeShader", "shader\\shadowShader\\depthCubeMap.vert", "shader\\shadowShader\\depthCubeMap.frag", "shader\\shadowShader\\depthCubeMap.geom");
		blurShader = new Shader("blurShader", "shader\\postShader\\screen.vert", "shader\\postShader\\blur.frag");
		twoTexShader = new Shader("twoTexShader", "shader\\postShader\\screen.vert", "shader\\postShader\\twoTexs.frag");
		gBufferShader = new Shader("gBufferShader", "shader\\deferredShader\\gBuffer.vert", "shader\\deferredShader\\gBuffer.frag");
		deferredShader = new Shader("deferredShader", "shader\\deferredShader\\deferred_shading.vert", "shader\\deferredShader\\deferred_shading.frag");
		ssaoShader = new Shader("ssaoShader", "shader\\deferredShader\\ssao.vert", "shader\\deferredShader\\ssao.frag");
		simpleBlurShader = new Shader("simpleBlurShader", "shader\\deferredShader\\simpleBlur.vert", "shader\\deferredShader\\simpleBlur.frag");
		fontShader = new Shader("fontShader", "shader\\specialShader\\fonts.vert", "shader\\specialShader\\fonts.frag");
		ballShader = new Shader("ballShader", "shader\\objectsShader\\ball.vert", "shader\\objectsShader\\ball.frag");
		// 更新着色器块索引
		camera->setShaderUBOIndex(modelShader, "Mat");
		camera->setShaderUBOIndex(cubeShader, "Mat");
		camera->setShaderUBOIndex(lightShader, "Mat");
		camera->setShaderUBOIndex(outlineShader, "Mat");
		camera->setShaderUBOIndex(skyboxShader, "Mat");
		camera->setShaderUBOIndex(instantShader, "Mat");
		camera->setShaderUBOIndex(gBufferShader, "Mat");
		camera->setShaderUBOIndex(ssaoShader, "Mat");
		camera->setShaderUBOIndex(fontShader, "Mat");
		camera->setShaderUBOIndex(ballShader, "Mat");
		// 网格与模型
		box = new Mesh(arr_vertex, arrVertex_N, POSITION | NORMAL | TEXCOORD, "res\\texture\\box1.png", "res\\texture\\box2.png");
		wall = new Mesh(arr_wall, arrWall_N, POSITION | NORMAL | TEXCOORD | TANGENT | BITANGENT, "res\\texture\\wall\\brickwall.jpg",
						"res\\texture\\wall\\brickwall.jpg", "res\\texture\\wall\\normal_map.png");
		redWall = new Mesh(arr_redWall, arrWall_N, POSITION | NORMAL | TEXCOORD | TANGENT | BITANGENT, "res\\texture\\redWall\\bricks2.jpg",
						   "res\\texture\\redWall\\bricks2.jpg", "res\\texture\\redWall\\bricks2_normal.jpg", "res\\texture\\redWall\\bricks2_disp.jpg");
		toyBox = new Mesh(arr_toyBox, arrWall_N, POSITION | NORMAL | TEXCOORD | TANGENT | BITANGENT, "res\\texture\\toybox\\toy_box_diffuse.png",
						  "res\\texture\\toybox\\toy_box_diffuse.png", "res\\texture\\toybox\\toy_box_normal.png", "res\\texture\\toybox\\toy_box_disp.png");
		ground = new Mesh(arr_floor, arrFloor_N, POSITION | NORMAL | TEXCOORD, "res\\texture\\box4.png", "res\\texture\\box4.png");
		light = new Mesh(arr_vertex, arrVertex_N, POSITION | NORMAL | TEXCOORD);
		skybox = new Mesh(arr_vertex, arrVertex_N, POSITION | NORMAL | TEXCOORD, cubePaths);
		human = new Model("C:\\Users\\34181\\Desktop\\code-demo\\gitstudy\\glLearn\\res\\3dmodels\\hutao\\胡桃.obj");
		rock = new Model("C:\\Users\\34181\\Desktop\\code-demo\\gitstudy\\glLearn\\res\\3dmodels\\rock\\rock.obj");

		int longitude = 60;
		int latitude = 60;
		size_t sphereArraySize = longitude * latitude * 6 * 5 * sizeof(GLfloat);
		GLfloat *sphereArray = (GLfloat *)malloc(sphereArraySize);
		createSphere(sphereArray, longitude, latitude);
		sphere = new Mesh(sphereArray, sphereArraySize, POSITION | TEXCOORD, "res\\texture\\360.jpg");
		free(sphereArray);

		// 模型矩阵
		for (int i = 0; i < 10; i++)
		{
			boxMat[i] = glm::translate(glm::mat4(1.0f), offsetModel[i]);
			boxMat[i] = glm::rotate(boxMat[i], glm::radians(20.0f * i), glm::vec3(1.0f, i, i));
		}
		// rock
		rockMat = new glm::mat4[rockNum];
		float radius = 50.0f;
		float rockOffsetMax = 2.5f;
		srand(glfwGetTime());
		for (int i = 0; i < rockNum; i++)
		{
			glm::mat4 model;
			// 位移
			float radians = (float)i / (float)rockNum * 360.0f;
			glm::vec3 rockPos;
			float rockOffset = (rand() % (int)(2 * rockOffsetMax * 100)) / 100.0f - rockOffsetMax; // 这里乘以100再除以100提高精度
			rockPos.x = (radius + rockOffset) * cos(glm::radians(radians));
			rockPos.z = (radius + rockOffset) * sin(glm::radians(radians));
			rockPos.y = rockOffset * ((rand() % 800) / 1000.0f - 0.4f); // 让y轴范围为(-0.4*rockOffset,0.4*rockOffset)，上下更加扁平
			model = glm::translate(glm::mat4(1.0f), rockPos);
			// 缩放
			float scale = (rand() % 21 + 5) / 1000.0f; // 0.05到0.25之间缩放
			model = glm::scale(model, glm::vec3(scale));
			// 旋转
			float angle = rand() % 360; // 0到360度旋转
			model = glm::rotate(model, glm::radians(angle), glm::vec3(0.4f, 0.6, 0.8f));

			rockMat[i] = model;
		}
		GLuint instanceVBO;
		glGenBuffers(1, &instanceVBO);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, rockNum * sizeof(glm::mat4), &rockMat[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		for (unsigned int i = 0; i < rock->meshes.size(); i++)
		{
			GLuint VAO = rock->meshes[i].getVAO();
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
			glEnableVertexAttribArray(7);
			glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)0);
			glEnableVertexAttribArray(8);
			glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4)));
			glEnableVertexAttribArray(9);
			glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(2 * sizeof(glm::vec4)));
			glEnableVertexAttribArray(10);
			glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(3 * sizeof(glm::vec4)));
			glVertexAttribDivisor(7, 1); // 1是属性除数,等于0时每次更新顶点时更新,等于1时每次更新实例时更新,等于3时每3次更新实例时更新
			glVertexAttribDivisor(8, 1);
			glVertexAttribDivisor(9, 1);
			glVertexAttribDivisor(10, 1);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		// noiseMap生成
		std::random_device rd;
		std::default_random_engine engine(rd());
		std::uniform_real_distribution<float> randomFloat(0.0f, 1.0f);
		std::vector<glm::vec3> ssaoNoise;
		for (int i = 0; i < 16; i++)
		{
			glm::vec3 noise =
				{
					randomFloat(engine) * 2.0f - 1.0f,
					randomFloat(engine) * 2.0f - 1.0f,
					0.0f // z方向为0
				};
			ssaoNoise.emplace_back(noise);
		}
		glGenTextures(1, &noiseMap);
		glBindTexture(GL_TEXTURE_2D, noiseMap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // 注意要重复纹理
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
		// 采样核心半球生成
		for (int i = 0; i < kernelSize; i++)
		{
			glm::vec3 sample =
				{
					randomFloat(engine) * 2.0f - 1.0f,
					randomFloat(engine) * 2.0f - 1.0f,
					randomFloat(engine) // z正半球
				};
			sample = glm::normalize(sample);
			sample *= randomFloat(engine);
			ssaoSamples.emplace_back(sample);
		}
		// 注意只有通过动态内存分配才能使纹理绑定的对象的生命周期为全局(空纹理会在绑定对象不存在时丢失缓冲区)
		finalFBO = new FrameBuffer(WIDTH, HEIGHT);
		texFBO = new FrameBuffer(WIDTH, HEIGHT);
		twoTexFBO = new FrameBuffer(WIDTH, HEIGHT, false, 2);
		pingpongFBO = new FrameBuffer[2]{FrameBuffer(WIDTH, HEIGHT), FrameBuffer(WIDTH, HEIGHT)};
		shadowFBO = new FrameBuffer(SHADOW_WIDTH, SHADOW_HEIGHT, true);
		spotShadowFBO = new FrameBuffer(SHADOW_WIDTH, SHADOW_HEIGHT, true);
		gBufferFBO = new FrameBuffer(WIDTH, HEIGHT, false, 3);
		ssaoFBO = new FrameBuffer(WIDTH, HEIGHT);
		ssaoBlurFBO = new FrameBuffer(WIDTH, HEIGHT);
	}
	void game_free()
	{
		delete camera;
		delete font;
		delete box;
		delete wall;
		delete redWall;
		delete toyBox;
		delete ground;
		delete light;
		delete skybox;
		delete human;
		delete rock;
		delete sphere;
		delete[] rockMat;
		delete cubeShader;
		delete modelShader;
		delete lightShader;
		delete outlineShader;
		delete screenShader;
		delete skyboxShader;
		delete instantShader;
		delete depthShader;
		delete depthCubeShader;
		delete blurShader;
		delete twoTexShader;
		delete gBufferShader;
		delete deferredShader;
		delete ssaoShader;
		delete simpleBlurShader;
		delete fontShader;
		delete ballShader;
		glfwTerminate(); // 不要忘记释放glfw资源
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		delete finalFBO;
		delete texFBO;
		delete[] pingpongFBO;
		delete shadowFBO;
		delete spotShadowFBO;
		delete gBufferFBO;
		delete ssaoFBO;
		delete ssaoBlurFBO;
		glDeleteVertexArrays(1, &quadVAO);
		glDeleteBuffers(1, &quadVBO);
		glDeleteTextures(1, &noiseMap);
		deleteSound(s1);
		deleteSound(s2);
		music.systemFree();
	}
	void gameLogic()
	{
		// LOGIC && RENDER
		// lightLogic
		float t = glfwGetTime();
		lightPos.x = 3 * sin(t);
		lightPos.z = 3 * cos(t);
		//  lightColor = {sin(0.2f * t + 2 * i) * 0.5f + 0.5f, sin(0.5f * t + 2 * i) * 0.5f + 0.5f, sin(0.7f * t + 2 * i) * 0.5f + 0.5f};
		//  lightColor = {1.0f, 1.0f, 1.0f};
		dotLight = {lightPos, 0.1f * dotColor, 0.5f * dotColor, dotColor, 1.0f, 0.09f, 0.0032f};
		dotLightMat = glm::scale(glm::translate(unitMat, dotLight.pos), glm::vec3(0.2f));
		dotShadowMat[0] = dotShadowProj * glm::lookAt(dotLight.pos, dotLight.pos + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
		dotShadowMat[1] = dotShadowProj * glm::lookAt(dotLight.pos, dotLight.pos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0));
		dotShadowMat[2] = dotShadowProj * glm::lookAt(dotLight.pos, dotLight.pos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
		dotShadowMat[3] = dotShadowProj * glm::lookAt(dotLight.pos, dotLight.pos + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0));
		dotShadowMat[4] = dotShadowProj * glm::lookAt(dotLight.pos, dotLight.pos + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0));
		dotShadowMat[5] = dotShadowProj * glm::lookAt(dotLight.pos, dotLight.pos + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0));
		spotLight.pos = lightPos + glm::vec3(1.0f, 2.0f, -1.5f);
		spotLight.front = glm::normalize(-spotLight.pos);
		spotLight.ambient = 0.01f * spotColor;
		spotLight.diffuse = 0.7f * spotColor;
		spotLight.specular = spotColor;
		// SOUND
		music.set3DPosition(s1, sin(t), cos(t), 0);
		music.updateSystem();
	}
	void rendGUI()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		// 设置下一个窗口的位置和大小
		ImGui::SetNextWindowPos({0, 0});
		ImGui::SetNextWindowSize({WIDTH / 5, HEIGHT});
		// GUI窗口
		ImGui::Begin("Settings", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
		if (ImGui::Button("点击我"))
			printf("\npress");
		ImGui::InputTextMultiline("input text", textBuffer, sizeof(textBuffer), ImVec2(0, 0), ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::Text(textBuffer);
		double x;
		ImGui::InputDouble("input double", &x);
		ImGui::Text(std::to_string(x).c_str());
		if (ImGui::BeginListBox("listbox"))
		{
			static bool isSelected = false;
			static unsigned int index = 0; // 默认选中位置
			for (unsigned int i = 0; i < 10; i++)
			{
				isSelected = (index == i);
				if (ImGui::Selectable(("select" + std::to_string(i)).c_str(), isSelected))
				{
					x = i;
					index = i;
				}
			}
			ImGui::EndListBox();
		}
		static unsigned int index = 0;
		if (ImGui::BeginCombo("combo", std::to_string(index).c_str()))
		{
			static bool isSelected = false;
			for (unsigned int i = 0; i < 10; i++)
			{
				isSelected = (index == i);
				if (ImGui::Selectable(std::to_string(i).c_str(), isSelected))
				{
					x = 2 * i;
					index = i;
				}
			}
			ImGui::EndCombo();
		}
		ImGui::SliderFloat("height_scale", &height_scale, 0.0f, 1.0f);
		ImGui::SliderFloat("曝光度", &finalFBO->exposure, 0.0f, 10.0f);
		ImGui::SliderFloat("textScale", &textScale, 0.1f, 10.0f);
		ImGui::SliderFloat("textThickness", &text_thickness, 0.0f, 1.0f);
		ImGui::SliderFloat("textSoftness", &text_softness, 0.0f, 1.0f);
		ImGui::SliderFloat("outline_thickness", &outline_thickness, 0.0f, 1.0f);
		ImGui::SliderFloat("outline_softness", &outline_softness, 0.0f, 1.0f);
		ImGui::SliderInt("高斯模糊次数", &blurCount, 0, 15);
		ImGui::SliderFloat("ssao采样半径", &kernelRadius, 0.0f, 2.0f);
		ImGui::Checkbox("drawRocks", &drawRock);
		ImGui::Checkbox("skyBox_ON", &skyBox_ON);
		ImGui::Checkbox("dirLight_ON", &dirLight_ON);
		ImGui::Checkbox("dotLight_ON", &dotLight_ON);
		ImGui::Checkbox("spotLight_ON", &spotLight_ON);
		ImGui::Checkbox("伽马校正", &finalFBO->gammaCorrection);
		ImGui::Checkbox("HDR_ON", &finalFBO->HDR);
		ImGui::Checkbox("SSAO", &ssao_ON);
		ImGui::ColorEdit3("dotColor", (float *)&dotColor);
		ImGui::ColorEdit3("spotColor", (float *)&spotColor);
		ImGui::ColorEdit3("fontColor", (float *)&textColor);
		ImGui::ColorEdit3("outlineColor", (float *)&outlineColor);
		if (ImGui::BeginPopupModal("Exit Game", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::SetCursorPos({(ImGui::GetWindowWidth() - ImGui::CalcTextSize("退出游戏?").x) * 0.5f, 100.0f});
			ImGui::Text("退出游戏?");
			ImGui::SetCursorPos({0.0f, 180.0f});
			if (ImGui::Button("是", ImVec2(120, 0)))
			{
				ImGui::CloseCurrentPopup(); // 关闭对话框
				glfwSetWindowShouldClose(window, GL_TRUE);
			}
			ImGui::SameLine();
			if (ImGui::Button("否", ImVec2(120, 0)))
			{
				ImGui::CloseCurrentPopup(); // 关闭对话框
			}
			ImGui::EndPopup();
		}
		if (ImGui::Button("退出游戏"))
			ImGui::OpenPopup("Exit Game");
		ImGui::End();
	}
	void rendShadowMap()
	{
		// 定向光阴影贴图
		shadowFBO->bindSFBO();
		glClear(GL_DEPTH_BUFFER_BIT);
		depthShader->use();
		depthShader->unfmat4fv("shadowSpaceMat", dirShadowSpaceMat);
		// 绘制箱子
		for (int i = 0; i < 10; i++)
		{
			depthShader->unfmat4fv("model", boxMat[i]);
			box->Draw(depthShader);
		}
		// 绘制地面
		depthShader->unfmat4fv("model", unitMat);
		ground->Draw(depthShader);
		// 绘制人物
		depthShader->unfmat4fv("model", humanMat);
		human->Draw(depthShader);
		// 绘制墙
		depthShader->unfmat4fv("model", unitMat);
		wall->Draw(depthShader);
		// 绘制红墙
		depthShader->unfmat4fv("model", unitMat);
		redWall->Draw(depthShader);
		// 绘制玩具盒
		depthShader->unfmat4fv("model", unitMat);
		toyBox->Draw(depthShader);

		// 点光源阴影贴图
		shadowFBO->bindSFBO_Cube();
		glClear(GL_DEPTH_BUFFER_BIT);
		depthCubeShader->use();
		depthCubeShader->unfm1f("far_plane", far_plane);
		depthCubeShader->unfvec3fv("lightPos", dotLight.pos);
		for (int i = 0; i < 6; i++)
			depthCubeShader->unfmat4fv(("shadowCubeMat" + std::string("[") + std::to_string(i) + "]").c_str(), dotShadowMat[i]);
		// 绘制箱子
		for (int i = 0; i < 10; i++)
		{
			depthCubeShader->unfmat4fv("model", boxMat[i]);
			box->Draw(depthCubeShader);
		}
		// 绘制地面
		depthCubeShader->unfmat4fv("model", unitMat);
		ground->Draw(depthCubeShader);
		// 绘制人物
		depthCubeShader->unfmat4fv("model", humanMat);
		human->Draw(depthCubeShader);
		// 绘制墙
		depthCubeShader->unfmat4fv("model", unitMat);
		wall->Draw(depthCubeShader);
		// 绘制红墙
		depthCubeShader->unfmat4fv("model", unitMat);
		redWall->Draw(depthCubeShader);
		// 绘制玩具盒
		depthCubeShader->unfmat4fv("model", unitMat);
		toyBox->Draw(depthCubeShader);

		// 聚光灯阴影贴图
		spotShadowFBO->bindSFBO();
		glClear(GL_DEPTH_BUFFER_BIT);
		depthShader->use();
		spotShadowSpaceMat = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f) * glm::lookAt(spotLight.pos, spotLight.pos + spotLight.front, glm::vec3(0.0f, 1.0f, 0.0f));
		depthShader->unfmat4fv("shadowSpaceMat", spotShadowSpaceMat);
		// 绘制箱子
		for (int i = 0; i < 10; i++)
		{
			depthShader->unfmat4fv("model", boxMat[i]);
			box->Draw(depthShader);
		}
		// 绘制地面
		depthShader->unfmat4fv("model", unitMat);
		ground->Draw(depthShader);
		// 绘制人物
		depthShader->unfmat4fv("model", humanMat);
		human->Draw(depthShader);
		// 绘制墙
		depthShader->unfmat4fv("model", unitMat);
		wall->Draw(depthShader);
		// 绘制红墙
		depthShader->unfmat4fv("model", unitMat);
		redWall->Draw(depthShader);
		// 绘制玩具盒
		depthShader->unfmat4fv("model", unitMat);
		toyBox->Draw(depthShader);
	}
	void rendGBuffer()
	{
		gBufferFBO->bindFBO();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		// 传递的变量:mat4 model;bool isInstance;bool hasNormalMap;bool hasHeightMap;
		gBufferShader->use();
		gBufferShader->unfm1f("height_scale", height_scale);
		gBufferShader->unfvec3fv("viewerPos", camera->getCameraPos());
		// 绘制人物
		gBufferShader->unfm1i("isInstance", false);
		gBufferShader->unfm1i("hasNormalMap", false);
		gBufferShader->unfm1i("hasHeightMap", false);
		gBufferShader->unfmat4fv("model", humanMat);
		human->Draw(gBufferShader);
		// 绘制墙
		gBufferShader->unfmat4fv("model", unitMat);
		wall->Draw(gBufferShader);
		// 绘制球
		ballShader->unfmat4fv("model", unitMat);
		sphere->Draw(ballShader);
		// 绘制红墙
		gBufferShader->unfm1i("hasNormalMap", true);
		gBufferShader->unfm1i("hasHeightMap", true);
		gBufferShader->unfmat4fv("model", unitMat);
		redWall->Draw(gBufferShader);
		// 绘制玩具盒
		gBufferShader->unfmat4fv("model", unitMat);
		toyBox->Draw(gBufferShader);
		// 绘制箱子
		gBufferShader->unfm1i("hasNormalMap", false);
		gBufferShader->unfm1i("hasHeightMap", false);
		for (int i = 0; i < 10; i++)
		{
			gBufferShader->unfmat4fv("model", boxMat[i]);
			box->Draw(gBufferShader);
		}
		// 绘制地面
		gBufferShader->unfmat4fv("model", unitMat);
		ground->Draw(gBufferShader);
		// 绘制陨石
		if (drawRock)
		{
			gBufferShader->unfm1i("isInstance", true);
			rock->Draw(gBufferShader, rockNum);
			gBufferShader->unfm1i("isInstance", false);
		}
	}
	void deferredRend()
	{
		if (ssao_ON)
		{
			// 生成ssao贴图
			ssaoFBO->bindFBO();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			ssaoShader->use();
			ssaoShader->unfm1i("gPositionDepth", 0);
			ssaoShader->unfm1i("gNormal", 1);
			ssaoShader->unfm1i("noiseMap", 2);
			for (int i = 0; i < 2; i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, gBufferFBO->getTexture(i));
			}
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, noiseMap);
			for (int i = 0; i < kernelSize; i++)
				ssaoShader->unfvec3fv(("samples" + std::string("[") + std::to_string(i) + "]").c_str(), ssaoSamples[i]);
			ssaoShader->unfm1i("kernelSize", kernelSize);
			ssaoShader->unfm1f("radius", kernelRadius);
			drawQuad();
			// 模糊ssao贴图
			ssaoBlurFBO->bindFBO();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			simpleBlurShader->use();
			simpleBlurShader->unfm1i("ssaoTexture", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, ssaoFBO->getTexture());
			drawQuad();
		}
		// 延迟着色
		glBindFramebuffer(GL_READ_FRAMEBUFFER, gBufferFBO->getFBO());
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, texFBO->getFBO());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glBlitFramebuffer(0, 0, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT, GL_NEAREST);
		glDepthMask(GL_FALSE);
		deferredShader->use();
		deferredShader->unfmat4fv("dirShadowSpaceMat", dirShadowSpaceMat);
		deferredShader->unfmat4fv("spotShadowSpaceMat", spotShadowSpaceMat);
		deferredShader->unfm1i("gPositionDepth", 0);
		deferredShader->unfm1i("gNormal", 1);
		deferredShader->unfm1i("gDiffuseAndSpecular", 2);
		shadowFBO->bindSTexture(deferredShader, "dirShadowMap", 3);
		shadowFBO->bindSTexture_Cube(deferredShader, "dotShadowMap", 4);
		spotShadowFBO->bindSTexture(deferredShader, "spotShadowMap", 5);
		deferredShader->unfm1i("ssaoTexture", 6);
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, ssaoBlurFBO->getTexture());

		for (int i = 0; i < 3; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, gBufferFBO->getTexture(i));
		}
		deferredShader->unfDirLight("dirLight", &dirLight);
		deferredShader->unfDotLight("dotLight", &dotLight);
		deferredShader->unfSpotLight("spotLight", &spotLight);
		deferredShader->unfm1i("dirLight_ON", dirLight_ON);
		deferredShader->unfm1i("dotLight_ON", dotLight_ON);
		deferredShader->unfm1i("spotLight_ON", spotLight_ON);
		deferredShader->unfm1i("SSAO_ON", ssao_ON);
		deferredShader->unfm1f("near_plane", near_plane);
		deferredShader->unfm1f("far_plane", far_plane);
		deferredShader->unfvec3fv("viewerPos", camera->getCameraPos());
		drawQuad();
		// 渲染文本
		static const glm::mat4 fontProj = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT);
		fontShader->use();
		fontShader->unfvec3fv("textColor", textColor);
		fontShader->unfvec3fv("outlineColor", outlineColor);
		fontShader->unfmat4fv("projection", fontProj);
		fontShader->unfm1f("thickness", text_thickness);
		fontShader->unfm1f("softness", text_softness);
		fontShader->unfm1f("outline_thickness", outline_thickness);
		fontShader->unfm1f("outline_softness", outline_softness);
		utf8_to_wchar(wtestBuffer, 4096, textBuffer);
		font->rendText(wtestBuffer, glm::vec2(400.0f, 450.0f), textScale);
		glDepthMask(GL_TRUE);
		// 绘制光源
		lightShader->use();
		lightShader->unfvec3fv("lightColor", dotColor * 10.0f);
		lightShader->unfmat4fv("model", dotLightMat);
		light->Draw(lightShader);
		lightShader->unfvec3fv("lightColor", spotColor * 10.0f);
		lightShader->unfmat4fv("model", glm::scale(glm::translate(unitMat, spotLight.pos), glm::vec3(0.1f)));
		light->Draw(lightShader);
		// 绘制天空盒
		if (skyBox_ON)
		{
			glDepthFunc(GL_LEQUAL);
			skyboxShader->use();
			skybox->Draw(skyboxShader);
			glDepthFunc(GL_LESS);
		}
	}
	void postRend()
	{
		// texFBO->copy_MFBO_To_FBO(); // 还原texFBO的纹理
		twoTexShader->use();
		twoTexFBO->DrawTexture(texFBO->getTexture()); // 用texFBO的纹理渲染到twoTexFBO的两个纹理附件中
		int count = blurCount;						  // 高斯模糊的次数
		bool horizontal = true;
		bool isFirst = true;
		blurShader->use();
		for (int i = 0; i < count * 2; i++)
		{
			blurShader->unfm1i("horizontal", horizontal);
			pingpongFBO[!horizontal].DrawTexture(isFirst ? twoTexFBO->getTexture(1) : pingpongFBO[horizontal].getTexture());
			horizontal = !horizontal;
			if (isFirst)
				isFirst = false;
		}
		screenShader->use();
		screenShader->unfm1i("screenTexture", 0);
		screenShader->unfm1i("bloomTexture", 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, twoTexFBO->getTexture(0));
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, pingpongFBO[!horizontal].getTexture());
		finalFBO->Draw(screenShader, 0, true);
	}
	void drawQuad()
	{
		if (quadVAO == 0)
		{
			float quadArray[] =
				{
					-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// 左上
					1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	// 右上
					-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // 左下
					1.0f, -1.0f, 0.0f, 1.0f, 0.0f	// 右下
				};
			glGenVertexArrays(1, &quadVAO);
			glBindVertexArray(quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadArray), quadArray, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
		}
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}
};
#endif