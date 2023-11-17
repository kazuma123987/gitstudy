#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <tool.h>
#include <shader.h>
class Camera
{
public:
	Camera();
	void update();
	void updateMat(Shader shader);
	void keyboardInput(GLFWwindow* window);
	void curseInput(GLFWwindow* window);
	void scrollCallback(float offset);
	glm::vec3 getCameraPos();
	glm::mat4 getViewMat();
	glm::mat4 getProjMat();
private:
	float fov;
	float cameraSpeed;
	float curseSensitivity;
	float lastTime;
	float curTime;
	float pitch;
	float yaw;
	glm::vec3 cameraFront;
	glm::vec3 cameraPos;
	glm::vec3 worldUp;
	glm::mat4 view;//观察矩阵
	glm::mat4 proj;//透视投影矩阵
};

#endif // !_CAMERA_H_
