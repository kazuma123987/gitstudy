#include <main.h>
int main(int argc, char *argv[])
{
	if (gameInit() == -1)
		fputs("\nfailed to init the game", stderr);
	// 着色器
	SetCurrentDirectoryA(filePath);
	Shader cubeShader("cubeShader", "shader\\cube.vert", "shader\\cube.frag");
	Shader modelShader("modelShader", "shader\\model.vert", "shader\\model.frag");
	Shader lightShader("lightShader", "shader\\light.vert", "shader\\light.frag");
	Shader outlineShader("outlineShader", "shader\\outline.vert", "shader\\outline.frag");
	Shader screenShader("screenShader", "shader\\screen.vert", "shader\\screen.frag");
	Shader skyboxShader("skyboxShader", "shader\\skybox.vert", "shader\\skybox.frag");
	Shader instantShader("instantShader", "shader\\instant.vert", "shader\\instant.frag");
	Shader depthShader("depthShader", "shader\\depthMap.vert", "shader\\depthMap.frag");
	Shader depthCubeShader("depthCubeShader", "shader\\depthCubeMap.vert", "shader\\depthCubeMap.frag", "shader\\depthCubeMap.geom");
	Shader blurShader("blurShader","shader\\screen.vert","shader\\blur.frag");
	Shader twoTexShader("twoTexShader","shader\\screen.vert","shader\\twoTexs.frag");
	// 设置纹理y轴(V轴)翻转
	stbi_set_flip_vertically_on_load(true);
	/*--------------------模型参数设置--------------------*/
	// 创建或加载模型
	clock_t start = clock();
	Mesh box(arr_vertex, arrVertex_N, POSITION | NORMAL | TEXCOORD, "res\\texture\\box1.png", "res\\texture\\box2.png");
	Mesh wall(arr_wall, arrWall_N, POSITION | NORMAL | TEXCOORD | TANGENT | BITANGENT, "res\\texture\\wall\\brickwall.jpg",
			  "res\\texture\\wall\\brickwall.jpg", "res\\texture\\wall\\normal_map.png");
	Mesh redWall(arr_redWall, arrWall_N, POSITION | NORMAL | TEXCOORD | TANGENT | BITANGENT, "res\\texture\\redWall\\bricks2.jpg",
				 "res\\texture\\redWall\\bricks2.jpg", "res\\texture\\redWall\\bricks2_normal.jpg", "res\\texture\\redWall\\bricks2_disp.jpg");
	Mesh toyBox(arr_toyBox, arrWall_N, POSITION | NORMAL | TEXCOORD | TANGENT | BITANGENT, "res\\texture\\toybox\\toy_box_diffuse.png",
				"res\\texture\\toybox\\toy_box_diffuse.png", "res\\texture\\toybox\\toy_box_normal.png", "res\\texture\\toybox\\toy_box_disp.png");
	Mesh floor(arr_floor, arrFloor_N, POSITION | NORMAL | TEXCOORD, "res\\texture\\box4.png", "res\\texture\\box4.png");
	Mesh light(arr_vertex, arrVertex_N, POSITION | NORMAL | TEXCOORD);
	Mesh skybox(arr_vertex, arrVertex_N, POSITION | NORMAL | TEXCOORD, cubePaths);
	printf_s("\nMeshes load time:%dms", clock() - start);
	start = clock();
	// Model human("C:\\Users\\34181\\Desktop\\code-demo\\gitstudy\\glLearn\\res\\3dmodels\\nanosuit_reflection\\nanosuit.obj");
	Model human("C:\\Users\\34181\\Desktop\\code-demo\\gitstudy\\glLearn\\res\\3dmodels\\hutao\\胡桃.obj");
	Model rock("C:\\Users\\34181\\Desktop\\code-demo\\gitstudy\\glLearn\\res\\3dmodels\\rock\\rock.obj");
	printf_s("\nModels load time:%dms", clock() - start);

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
	glm::vec3 lightPos = glm::vec3(0.0f, 4.0f, 3.0f);

	// dirLight
	DirectLight dirLight = {glm::vec3(2.0f, -8.0f, 1.0f), glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(0.5f)};
	glm::mat4 shadowSpaceMat = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f) * glm::lookAt(-dirLight.dir, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// dotLight
	glm::vec3 dotColor = glm::vec3(1.0f);
	DotLight dotLight = {lightPos, 0.02f * dotColor, 0.5f * dotColor,  dotColor, 1.0f, 0.09f, 0.032f};
	glm::mat4 dotLightMat = glm::translate(unitMat, dotLight.pos);
	const float near_plane = 0.1f;
	const float far_plane = 100.0f;
	glm::mat4 dotShadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
	glm::mat4 dotShadowMat[6];
	// spotLight
	glm::vec3 spotColor = glm::vec3(1.0f);
	SpotLight spotLight = {glm::vec3(0.0f), glm::vec3(0.01f), glm::vec3(0.7f), glm::vec3(1.0f), 1.0f, 0.09f, 0.032f,
						   glm::cos(glm::radians(15.0f)), glm::cos(glm::radians(17.5f)), glm::vec3(0.0f, 0.0f, -1.0f)};
	// rock
	const int rockNum = 100000;
	glm::mat4 *rockMat = new glm::mat4[rockNum]; // 这里用栈会溢出(windows栈空间1MB,linux为4MB,可用-Wl,--stack=yourSize来让链接器增加栈空间)
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

	for (unsigned int i = 0; i < rock.meshes.size(); i++)
	{
		GLuint VAO = rock.meshes[i].getVAO();
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
	glEnable(GL_MULTISAMPLE); // 开启多重采样缓冲(在不使用帧缓冲时不需要额外处理)
	// 绑定回调函数
	glfwSetFramebufferSizeCallback(window, frame_size_callback);
	glfwSetScrollCallback(window, scrollCallback);
	// 帧缓冲对象(FrameBuffer Object)
	FrameBuffer finalFBO(WIDTH, HEIGHT);
	FrameBuffer texFBO(WIDTH,HEIGHT);
	FrameBuffer twoTexFBO(WIDTH,HEIGHT,false,2);
	FrameBuffer pingpongFBO[2]={FrameBuffer(WIDTH,HEIGHT),FrameBuffer(WIDTH,HEIGHT)};
	FrameBuffer shadowFBO(SHADOW_WIDTH, SHADOW_HEIGHT, true);
	FrameBuffer spotShadowFBO(SHADOW_WIDTH, SHADOW_HEIGHT, true);
	// 先更新着色器块索引
	camera->setShaderUBOIndex(&modelShader, "Mat");
	camera->setShaderUBOIndex(&cubeShader, "Mat");
	camera->setShaderUBOIndex(&lightShader, "Mat");
	camera->setShaderUBOIndex(&outlineShader, "Mat");
	camera->setShaderUBOIndex(&skyboxShader, "Mat");
	camera->setShaderUBOIndex(&instantShader, "Mat");

	/*--------------------渲染循环--------------------*/
	while (!glfwWindowShouldClose(window))
	{
		// INPUT
		press_close_window(window);
		mouse_button_input(window);
		keyboardInput(window);
		if (!isShowCursor)
		{
			camera->keyboardInput(window);
			camera->curseInput(window);
		}
		camera->update();
		camera->updateUBO(); // 直接通过UBO把view和proj矩阵以全局变量(块)的形式发送

		// LOGIC && RENDER
		// lightLogic
		float t = glfwGetTime();
		//lightPos.x = 3 * sin(t);
		//lightPos.z = 3 * cos(t);
		// lightColor = {sin(0.2f * t + 2 * i) * 0.5f + 0.5f, sin(0.5f * t + 2 * i) * 0.5f + 0.5f, sin(0.7f * t + 2 * i) * 0.5f + 0.5f};
		// lightColor = {1.0f, 1.0f, 1.0f};
		dotLight = {lightPos, 0.1f*dotColor, 0.5f * dotColor, dotColor, 1.0f, 0.09f, 0.0032f};
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

		// IMGUI
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
		char textBuffer[50] = "input text";
		ImGui::InputText("input text", textBuffer, sizeof(textBuffer), ImGuiInputTextFlags_EnterReturnsTrue);
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
		static bool isChecked;
		ImGui::Checkbox("check box", &isChecked);
		float slider[4];
		ImGui::SliderFloat4("slider", slider, 0.0f, 1.0f);
		static float height_scale = 0.1f;
		ImGui::SliderFloat("height_scale", &height_scale, 0.0f, 1.0f);
		ImGui::SliderFloat("曝光度", &finalFBO.exposure, 0.0f, 10.0f);
		static int blurCount=1;
		ImGui::SliderInt("高斯模糊次数",&blurCount,0,15);
		static bool drawRock = true;
		static bool skyBox_ON = false;
		static bool heightTexture_ON = false;
		static bool normalTexture_ON = false;
		static bool dirLight_ON = true;
		static bool dotLight_ON = true;
		static bool spotLight_ON = false;
		static bool reflect_ON = false;
		static bool Parallax_Occlustion_Mapping = true;
		ImGui::Checkbox("drawRocks", &drawRock);
		ImGui::Checkbox("skyBox_ON", &skyBox_ON);
		ImGui::Checkbox("normalTexture_ON", &normalTexture_ON);
		ImGui::Checkbox("heightTexture_ON", &heightTexture_ON);
		ImGui::Checkbox("视差遮蔽映射", &Parallax_Occlustion_Mapping);
		ImGui::Checkbox("dirLight_ON", &dirLight_ON);
		ImGui::Checkbox("dotLight_ON", &dotLight_ON);
		ImGui::Checkbox("spotLight_ON", &spotLight_ON);
		ImGui::Checkbox("reflect_ON", &reflect_ON);
		ImGui::Checkbox("伽马校正", &finalFBO.gammaCorrection);
		ImGui::Checkbox("HDR_ON", &finalFBO.HDR);
		ImGui::ColorEdit3("dotColor", (float *)&dotColor);
		ImGui::ColorEdit3("spotColor", (float *)&spotColor);
		if (ImGui::BeginPopupModal("Exit Game", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::SetCursorPos({(ImGui::GetWindowWidth() - ImGui::CalcTextSize("退出游戏?").x) * 0.5f, 100.0f});
			ImGui::Text("退出游戏?");
			ImGui::SetCursorPos({0.0f, 180.0f});
			if (ImGui::Button("是", ImVec2(120, 0)))
			{
				ImGui::CloseCurrentPopup(); // 关闭对话框
				break;
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

		/*------第一阶段处理(生成阴影贴图)------*/
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);

		// 定向光阴影贴图
		shadowFBO.bindSFBO();
		glClear(GL_DEPTH_BUFFER_BIT);
		depthShader.use();
		depthShader.unfmat4fv("shadowSpaceMat", shadowSpaceMat);
		// 绘制箱子
		for (int i = 0; i < 10; i++)
		{
			depthShader.unfmat4fv("model", boxMat[i]);
			box.Draw(&depthShader);
		}
		// 绘制地面
		depthShader.unfmat4fv("model", unitMat);
		floor.Draw(&depthShader);
		// 绘制人物
		depthShader.unfmat4fv("model", humanMat);
		human.Draw(&depthShader);

		// 点光源阴影贴图
		shadowFBO.bindSFBO_Cube();
		glClear(GL_DEPTH_BUFFER_BIT);
		depthCubeShader.use();
		depthCubeShader.unfm1f("far_plane", far_plane);
		depthCubeShader.unfvec3fv("lightPos", dotLight.pos);
		for (int i = 0; i < 6; i++)
			depthCubeShader.unfmat4fv(("shadowCubeMat" + std::string("[") + std::to_string(i) + "]").c_str(), dotShadowMat[i]);
		// 绘制箱子
		for (int i = 0; i < 10; i++)
		{
			depthCubeShader.unfmat4fv("model", boxMat[i]);
			box.Draw(&depthCubeShader);
		}
		// 绘制地面
		depthCubeShader.unfmat4fv("model", unitMat);
		floor.Draw(&depthCubeShader);
		// 绘制人物
		depthCubeShader.unfmat4fv("model", humanMat);
		human.Draw(&depthCubeShader);

		// 聚光灯阴影贴图
		spotShadowFBO.bindSFBO();
		glClear(GL_DEPTH_BUFFER_BIT);
		depthShader.use();
		glm::mat4 spotShadowSpaceMat = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f) *
									   glm::lookAt(spotLight.pos, spotLight.pos + spotLight.front, glm::vec3(0.0f, 1.0f, 0.0f));
		depthShader.unfmat4fv("shadowSpaceMat", spotShadowSpaceMat);
		// 绘制箱子
		for (int i = 0; i < 10; i++)
		{
			depthShader.unfmat4fv("model", boxMat[i]);
			box.Draw(&depthShader);
		}
		// 绘制地面
		depthShader.unfmat4fv("model", unitMat);
		floor.Draw(&depthShader);
		// 绘制人物
		depthShader.unfmat4fv("model", humanMat);
		human.Draw(&depthShader);

		/*------第二阶段处理(正常渲染)------*/
		texFBO.bindMFBO();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// 绘制光源
		lightShader.use();
		lightShader.unfvec3fv("lightColor", dotColor * 10.0f);
		lightShader.unfmat4fv("model", dotLightMat);
		light.Draw(&lightShader);
		lightShader.unfvec3fv("lightColor", spotColor * 10.0f);
		lightShader.unfmat4fv("model", glm::scale(glm::translate(unitMat, spotLight.pos), glm::vec3(0.1f)));
		light.Draw(&lightShader);
		// modelLogic
		modelShader.use();
		modelShader.unfm1i("heightTexture_ON", heightTexture_ON);
		modelShader.unfm1i("normalTexture_ON", normalTexture_ON);
		modelShader.unfm1i("dirLight_ON", dirLight_ON);
		modelShader.unfm1i("dotLight_ON", dotLight_ON);
		modelShader.unfm1i("spotLight_ON", spotLight_ON);
		modelShader.unfm1i("reflect_ON", reflect_ON);
		modelShader.unfm1i("Parallax_Occlustion_Mapping", Parallax_Occlustion_Mapping);
		modelShader.unfm1f("height_scale", height_scale);

		modelShader.unfmat4fv("spotShadowSpaceMat", spotShadowSpaceMat);
		modelShader.unfmat4fv("shadowSpaceMat", shadowSpaceMat);
		shadowFBO.bindSTexture(&modelShader, "shadowMap", 5); // 深度贴图
		shadowFBO.bindSTexture_Cube(&modelShader, "shadowCubeMap", 6);
		spotShadowFBO.bindSTexture(&modelShader, "spotShadowMap", 7);
		modelShader.unfm1i("texture_cube1", 4);					   // 设置要传入GL_TEXTURE4
		glActiveTexture(GL_TEXTURE4);							   // 激活纹理单元4
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.textures[0].id); // 把立方体纹理绑定到当前纹理单元
		modelShader.unfDirLight("dirLight", &dirLight);
		modelShader.unfDotLight("dotLight", &dotLight);
		modelShader.unfSpotLight("spotLight", &spotLight);
		modelShader.unfvec3fv("viewerPos", camera->getCameraPos());
		modelShader.unfm1f("material.shininess", 32.0f);
		modelShader.unfm1f("far_plane", far_plane);
		// 绘制人物
		glm::mat3 normMat;
		normMat = glm::mat3(glm::transpose(glm::inverse(humanMat)));
		modelShader.unfmat3fv("normMat", normMat);
		modelShader.unfmat4fv("model", humanMat);
		human.Draw(&modelShader);
		// 绘制墙
		normMat = glm::mat3(glm::transpose(glm::inverse(unitMat)));
		modelShader.unfmat3fv("normMat", normMat);
		modelShader.unfmat4fv("model", unitMat);
		wall.Draw(&modelShader);
		// 绘制红墙
		normMat = glm::mat3(glm::transpose(glm::inverse(unitMat)));
		modelShader.unfmat3fv("normMat", normMat);
		modelShader.unfmat4fv("model", unitMat);
		redWall.Draw(&modelShader);
		// 绘制玩具盒
		normMat = glm::mat3(glm::transpose(glm::inverse(unitMat)));
		modelShader.unfmat3fv("normMat", normMat);
		modelShader.unfmat4fv("model", unitMat);
		toyBox.Draw(&modelShader);
		// cubeLogic
		cubeShader.use();
		cubeShader.unfm1i("normalTexture_ON", normalTexture_ON);
		cubeShader.unfm1i("dirLight_ON", dirLight_ON);
		cubeShader.unfm1i("dotLight_ON", dotLight_ON);
		cubeShader.unfm1i("spotLight_ON", spotLight_ON);

		cubeShader.unfmat4fv("spotShadowSpaceMat", spotShadowSpaceMat);
		cubeShader.unfmat4fv("shadowSpaceMat", shadowSpaceMat);
		shadowFBO.bindSTexture(&cubeShader, "shadowMap", 5); // 深度贴图
		shadowFBO.bindSTexture_Cube(&cubeShader, "shadowCubeMap", 6);
		spotShadowFBO.bindSTexture(&cubeShader, "spotShadowMap", 7);
		cubeShader.unfDirLight("dirLight", &dirLight);
		cubeShader.unfDotLight("dotLight", &dotLight);
		cubeShader.unfSpotLight("spotLight", &spotLight);
		cubeShader.unfvec3fv("viewerPos", camera->getCameraPos());
		cubeShader.unfm1f("material.shininess", 32.0f);
		cubeShader.unfm1f("far_plane", far_plane);
		// 绘制箱子
		for (int i = 0; i < 10; i++)
		{
			cubeShader.unfmat4fv("model", boxMat[i]);
			normMat = glm::mat3(glm::transpose(glm::inverse(boxMat[i])));
			cubeShader.unfmat3fv("normMat", normMat);
			box.Draw(&cubeShader);
		}
		// 绘制地面
		cubeShader.unfmat4fv("model", unitMat);
		normMat = glm::mat3(glm::transpose(glm::inverse(unitMat)));
		cubeShader.unfmat3fv("normMat", normMat);
		floor.Draw(&cubeShader);
		// 绘制陨石
		if (drawRock)
		{
			instantShader.use();
			rock.Draw(&instantShader, rockNum);
		}
		// 绘制天空盒
		if (skyBox_ON)
		{
			glDepthFunc(GL_LEQUAL);
			skyboxShader.use();
			skybox.Draw(&skyboxShader);
			glDepthFunc(GL_LESS);
		}

		/*------第三阶段处理(后期处理)------*/
		texFBO.copy_MFBO_To_FBO();//还原texFBO的纹理
		twoTexShader.use();
		twoTexFBO.DrawTexture(texFBO.getTexture());//用texFBO的纹理渲染到twoTexFBO的两个纹理附件中
		int count=blurCount;//高斯模糊的次数
		bool horizontal=true;
		bool isFirst=true;
		blurShader.use();
		for(int i=0;i<count*2;i++)
		{
			blurShader.unfm1i("horizontal",horizontal);
			pingpongFBO[!horizontal].DrawTexture(isFirst?twoTexFBO.getTexture(1):pingpongFBO[horizontal].getTexture());
			horizontal=!horizontal;
			if(isFirst)isFirst=false;
		}
		screenShader.use();
		screenShader.unfm1i("screenTexture",0);
		screenShader.unfm1i("bloomTexture",1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,twoTexFBO.getTexture(0));
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,pingpongFBO[!horizontal].getTexture());
		finalFBO.Draw(&screenShader,0,true);			

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// SOUND
		music.set3DPosition(s1, sin(t), cos(t), 0);
		music.updateSystem();

		// 设置标题
		rendFPS(window);

		// EVENTS && DISPLAY
		glfwSwapBuffers(window);
		glfwPollEvents(); // 处理窗口交互事件等
	}

	/*--------------------释放内存--------------------*/
	glfwTerminate(); // 不要忘记释放glfw资源
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	finalFBO.destory();
	texFBO.destory();
	pingpongFBO[0].destory();
	pingpongFBO[1].destory();
	shadowFBO.destory();
	spotShadowFBO.destory();
	deleteSound(s1);
	deleteSound(s2);
	delete (camera);
	delete[] rockMat;
	music.systemFree();
	return 0;
}