#include "camera.h"
void Camera::updateSpeed() // 更新摄像机移动速度
{
    curTime = glfwGetTime();
    deltaTime = curTime - lastTime;
    lastTime = curTime;
    cameraSpeed = deltaTime * 4.0f;
}
void Camera::updatePosition(Shader *shader, const char *nameView, const char *nameProj) // 需要先使用(use)着色器
{
    viewMat = glm::lookAt(cameraPos, cameraPos + cameraFront, worldUp);
    projMat = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    shader->unfmat4fv(nameView, viewMat);
    shader->unfmat4fv(nameProj, projMat);
}
void Camera::keyboardControl(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            cameraPos += cameraFront * (cameraSpeed * 2);
        else
            cameraPos += cameraFront * cameraSpeed;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            cameraPos -= cameraFront * (cameraSpeed * 2);
        else
            cameraPos -= cameraFront * cameraSpeed;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, worldUp)) * cameraSpeed;
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, worldUp)) * cameraSpeed;
    cameraPos.y = 0; // 这里限制了摄像机只能在xz平面移动
}
void Camera::curseControl(GLFWwindow *window)
{
    // 镜头旋转
    static bool isFirst = true;
    static float lastX = 0;
    static float lastY = 0;
    static double xPos = 0;
    static double yPos = 0;
    glfwGetCursorPos(window, &xPos, &yPos);
    if (isFirst)
    {
        lastX = xPos;
        lastY = yPos;
        isFirst = false;
    }
    float xOffset = (xPos - lastX) * sensitivity;
    float yOffset = (yPos - lastY) * sensitivity;
    lastX = xPos;
    lastY = yPos;
    pitch += yOffset; // 上下移动,沿x轴旋转
    yaw += xOffset;   // 左右移动,沿y轴旋转
    if (pitch > 89.0f)
        pitch = 89.0f;
    else if (pitch < -89.0f)
        pitch = -89.0f;
    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    front.y = -sin(glm::radians(pitch));
    front.z = -cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    cameraFront = glm::normalize(front);
}
void Camera::scrollCallback(float offset)
{
    fov -= (float)offset;
    if (fov < 1.0f)
        fov = 1.0f;
    else if (fov > 60.0f)
        fov = 60.0f;
}