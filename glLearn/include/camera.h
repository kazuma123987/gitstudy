#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <tool.h>
#include <shader.h>
class Camera
{
public:
	Camera();
	~Camera()
	{
		destroyCamera();
	};
	void destroyCamera()
	{
		glDeleteBuffers(1, &UBO);
	}
	void update();
	void updateMat(Shader *shader)
	{
		shader->unfmat4fv("view", view);
		shader->unfmat4fv("proj", proj);
	}
	void updateUBO()
	{
		glBindBuffer(GL_UNIFORM_BUFFER,UBO);
		glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(glm::mat4),glm::value_ptr(view));
		glBufferSubData(GL_UNIFORM_BUFFER,sizeof(glm::mat4),sizeof(glm::mat4),glm::value_ptr(proj));
		glBindBuffer(GL_UNIFORM_BUFFER,0);
	}
	void keyboardInput(GLFWwindow *window);
	void curseInput(GLFWwindow *window);
	void scrollCallback(float offset);
	// 设置shader块索引
	void setShaderUBOIndex(Shader *shader, const char *blockName, int index = 0)
	{
		glUniformBlockBinding(shader->shaderProgram, glGetUniformBlockIndex(shader->shaderProgram, blockName), index);
	}
	// 使用前先设置shader块索引
	void setUBOIndex(int index)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, index, UBO);
	}
	glm::vec3 getCameraPos()
	{
		return cameraPos;
	}
	glm::vec3 getCameraFront()
	{
		return cameraFront;
	}
	glm::mat4 getViewMat()
	{
		return view;
	}
	glm::mat4 getProjMat()
	{
		return proj;
	}

private:
	GLuint UBO;
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
	glm::mat4 view; // 观察矩阵
	glm::mat4 proj; // 透视投影矩阵
};

#endif // !_CAMERA_H_
