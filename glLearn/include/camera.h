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
	void setViewMat(glm::mat4 view)
	{
		this->view=view;
	}
	void setProjMat(glm::mat4 proj)
	{
		this->proj=proj;
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
	glm::quat qua;//四元数,本质为绕着任意轴旋转一个角度,不同于欧拉角绕x,y,z角旋转,避免万向节死锁问题
	glm::vec3 cameraFront;
	glm::vec3 cameraPos;
	glm::vec3 worldUp;
	glm::mat4 view; // 观察矩阵
	glm::mat4 proj; // 透视投影矩阵,通过该矩阵与观察矩阵可以把世界空间坐标转换为裁切空间坐标,裁切空间x',y',z'范围都是[-1,1]
	//对于xy,按照远近平面的相似三角形求值,对于z',若z'=f(z),则f(near)=-1,f(far)=1,且z'=[((1/(z+3)−1/near)/(1/far−1/near))⋅2−1]
	//对于深度值,其范围为[0,1],depth=(z'+1)/2,故depth=(1/(z+3)−1/near)/(1/far−1/near),这里的(z+3)是因为相机的位置在z=-3处

	//总结1:裁切空间z'∈[-1,1],depth∈[0,1],depth=z'*0.5+0.5,这个转换就是实际的深度坐标与裁切空间z'坐标的实际转换公式
	//总结2:对于正交投影矩阵,深度变化是线性的,即depth=((z-camera_z)−near)/(far−near),
	//总结3:对于透视投影矩阵,深度变化是非线性的,即depth=(1/(z-camera_z)−1/near)/(1/far−1/near)
};

#endif // !_CAMERA_H_
