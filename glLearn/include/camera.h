#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <tool.h>
#include <shader.h>
class Camera
{
public:
	Camera();
	//更新观察矩阵、投影矩阵和相机移动速度
	void update();
	//把观察矩阵和投影矩阵传到uniform变量
	void updateMat(Shader shader);
	//键盘WASD控制相机位置向量
	void keyboardInput(GLFWwindow* window);
	//鼠标移动位置控制欧拉角大小
	void curseInput(GLFWwindow* window);
	//鼠标滚轮控制相机投影矩阵的角度fov(影响视野)
	void scrollCallback(float offset);
	glm::vec3 getCameraPos();
	glm::vec3 getCameraFront();
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
