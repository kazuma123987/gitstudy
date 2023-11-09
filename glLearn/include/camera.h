#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "tool.h"
#include "shader.h"
#define WIDTH 700
#define HEIGHT 700
class Camera
{
private:
    glm::mat4 viewMat = glm::mat4(1.0f);
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);    // 摄像机位置
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // 前方偏移量
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);      // 世界坐标上方
    glm::mat4 projMat = glm::mat4(1.0f);
    float fov=45.0f;
    float cameraSpeed = 0.05f;
    float pitch = 0.0f;
    float yaw = 0.0f;
    float curTime = 0;
    float lastTime = 0;
    float deltaTime = 0;
    float sensitivity = 0.05;

public:
    void updateSpeed();                                    // 更新摄像机移动速度
    void updatePosition(Shader *shader, const char *name,const char *nameProj); // 需要先使用(use)着色器
    void keyboardControl(GLFWwindow *window);
    void curseControl(GLFWwindow *window);
    void scrollCallback(float offset);
};
#endif