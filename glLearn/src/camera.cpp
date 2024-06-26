#include <camera.h>
Camera::Camera(GLfloat near_point, GLfloat far_point)
	: near_point(near_point), far_point(far_point)
{
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	qua = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
	view = glm::mat4(1.0f);
	proj = glm::mat4(1.0f);
	fov = 45.0f;
	cameraSpeed = 0.05f;
	curseSensitivity = 0.05f;
	lastTime = curTime = glfwGetTime();
	pitch = 0.0f;
	yaw = 0.0f;
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);
}
void Camera::update() // 需要先使用(use)着色器
{
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, worldUp);
	proj = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, this->near_point, this->far_point);
	// proj=glm::ortho(0.0f,(float)WIDTH,0.0f,(float)HEIGHT,0.1f,10000.0f);
	curTime = glfwGetTime();
	cameraSpeed = (curTime - lastTime) * 5.0f;
	lastTime = curTime;
}
void Camera::keyboardInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			cameraPos += cameraFront * (cameraSpeed * 2.0f);
		else
			cameraPos += cameraFront * cameraSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			cameraPos -= cameraFront * (cameraSpeed * 2.0f);
		else
			cameraPos -= cameraFront * cameraSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, worldUp)) * cameraSpeed;
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, worldUp)) * cameraSpeed;
}
void Camera::curseInput(GLFWwindow *window)
{
	static double xPos = 0.0f;
	static double yPos = 0.0f;
	static float lastX = 0.0f;
	static float lastY = 0.0f;
	static bool isFirst = TRUE;
	glfwGetCursorPos(window, &xPos, &yPos);
	if (isFirst)
	{
		lastX = xPos;
		lastY = yPos;
		isFirst = FALSE;
	}
	float offsetX = xPos - lastX;
	float offsetY = yPos - lastY;
	lastX = xPos;
	lastY = yPos;
	// glm::quat up_q=glm::angleAxis(glm::radians(offsetY*0.1f),glm::vec3(1.0f,0.0f,0.0f));
	// glm::quat right_q=glm::angleAxis(glm::radians(offsetX*0.1f),glm::vec3(0.0f,1.0f,0.0f));
	// qua*=(up_q*right_q);
	// cameraFront=glm::normalize(glm::vec3(glm::mat4_cast(qua)*glm::vec4(0.0f,0.0f,-1.0f,1.0f)));
	pitch += offsetY * curseSensitivity;
	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;
	yaw += offsetX * curseSensitivity;
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	front.y = -sin(glm::radians(pitch));
	front.z = -cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}
void Camera::scrollCallback(float offset)
{
	fov += offset;
	if (fov < 1.0f)
		fov = 1.0f;
	else if (fov > 90.0f)
		fov = 90.0f;
}