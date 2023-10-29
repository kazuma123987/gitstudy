#include "test.h"
#include "fmod/fmod.h"
#include "mmsystem.h"
#include "glad/glad.h"  //glad.h必须放在glfw3.h前面，glad可以查找gl、glu、glex、wgl、glx的函数指针以方便调用其函数
#include "GLFW/glfw3.h" //轻量级跨平台工具库，提供渲染物体最低限度的API（管理窗口、读取输入、处理事件）
//VAO:乘坐高铁的人们 VBO:高铁 显存：高铁的终点站
//VAO会存储顶点属性的更改和对应的缓存对象
const char *vsh="#version 330 core\n"
"layout (location=0) in vec3 pos;\n"
"void main()\n"
"{\n"
"gl_Position=vec4(pos.x,pos.y,pos.z,1);\n"
"}";
const char *fsh="#version 330 core\n"
"out vec4 fcolor;\n"
"void main()\n"
"{\n"
"fcolor=vec4(0.5,0.5,0,1);\n"
"}";
void frame_size_callback(GLFWwindow *window,int width,int height);
void press_close_window(GLFWwindow *window);
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);//注意设置的glfw上下文版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    #ifdef _APPLE_
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    #endif
    GLFWwindow *window=glfwCreateWindow(800,600,"game",NULL,NULL);
    if(window==NULL)
    {
        fputs("\nfailed to create window",stderr);
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);//设置window为gl要处理的窗口环境
    glfwSetFramebufferSizeCallback(window,frame_size_callback);
    //使用glad加载opengl库
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fputs("\nfailed to init glad",stderr);
        glfwTerminate();
        return -1;
    }
    //顶点着色器vertexShader
    GLuint vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vsh,NULL);
    glCompileShader(vertexShader);
    int flag_v=1;
    char info_v[512];
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&flag_v);
    if(!flag_v)
    {
        glGetShaderInfoLog(vertexShader,512,NULL,info_v);
        fputs(info_v,stderr);
    }
    //片段着色器fragmentShader
    GLuint fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fsh,NULL);
    glCompileShader(fragmentShader);
    int flag_f=1;
    char info_f[512];
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&flag_f);
    if(!flag_f)
    {
        glGetShaderInfoLog(fragmentShader,512,NULL,info_f);
        fputs(info_f,stderr);
    }
    //着色器程序shaderProgram
    GLuint shaderProgram=glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    int flag_p=1;
    char info_p[512];
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&flag_p);
    if(!flag_p)
    {
        glGetProgramInfoLog(shaderProgram,512,NULL,info_p);
        fputs(info_p,stderr);
    }
    //已经创建完着色器程序，删除不需要的着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //顶点数组和索引
    float arr_vertex[]=
    {
        0,0,0,
        0.5f,0.5f,0,
        -0.5f,0.5f,0,
        0,0,0,
        -0.5f,-0.5f,0,
        0.5f,-0.5f,0
    };
    unsigned int arr_index[]=
    {
        0,1,3,
        1,2,3,
    };
    //通过glGen创建顶点数组对象VAO，顶点缓冲对象VBO，元素（索引）缓冲对象EBO名称；
    //通过glBind创建VAO、VBO、EBO对象（再次使用glBind会激活对象）
    GLuint VAO,VBO,EBO;
    glGenVertexArrays(1,&VAO);//生成1个VAO"名称"并存放在变量中,可以GLuint VAO[5];glGenVertexArrays(5,VAO)这样创建5个VAO名称到数组中
    glGenBuffers(1,&VBO);//生成1个缓存对象"名称"并存于变量中，也可以用数组方式存储，同上
    glGenBuffers(1,&EBO);//生成1个缓存对象"名称"并存于变量中，也可以用数组方式存储，同上
    glBindVertexArray(VAO);//为当前VAO名称创建一个顶点数组对象，并将VAO名称与VAO对象关联起来，
    //通常glBindVertexArray(Name)有三个作用：
    //1.如果Name没绑定顶点数组对象，则为其创建并绑定该VAO对象
    //2.如果Name已经绑定过VAO对象，则将其绑定的对象设置为当前活动的VAO对象（激活Name关联的VAO对象）
    //3.如果Name是0，则激活默认VAO对象
    glBindBuffer(GL_ARRAY_BUFFER,VBO);//为当前缓存对象名称创建一个VBO对象（利用GL_ARRAY_BUFFER选项）并将名称与对象关联起来
    //glBindBuffer(target,Buffer_Name)三个作用:
    //1.若名称未绑定缓存对象，创建并绑定新的缓存对象，缓存对象类型按target决定,如target为时GL_ARRAY_BUFFER创建并绑定新的数组缓存对象
    //2.若名称已绑定缓存对象，激活该名称绑定的缓存对象为当前活动缓存对象
    //3.如果名称为0，则还原当前活动缓存对象为默认状态
    glBufferData(GL_ARRAY_BUFFER,sizeof(arr_vertex),arr_vertex,GL_STATIC_DRAW);//拷贝数组数据到缓存对象内存中（显存）
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);//创建并关联新的EBO对象
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(arr_index),arr_index,GL_STATIC_DRAW);//拷贝数组数据到显存
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);//设置顶点属性（VertexAttribute)
    glEnableVertexAttribArray(0);//使顶点属性指针对应的顶点属性起作用
    glBindBuffer(GL_ARRAY_BUFFER,0);//解除绑定的VBO对象
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);//不要解绑EBO对象，因为VAO会使用EBO的数据
    glBindVertexArray(0);//解绑VAO对象
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//线框模式绘图
    //glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);//填充模式绘图（默认）

    while(!glfwWindowShouldClose(window))
    {
        //inputs
        press_close_window(window);
        //shader
        glClearColor(0.1,0.2,0.3,1);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);//使用着色器程序
        glBindVertexArray(VAO);//绑定VAO对象
        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);//利用索引缓存对象画三角形
        glDrawArrays(GL_TRIANGLES,0,3);
        //output
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1,&VAO);//删除VAO绑定的一个VAO对象
    glDeleteBuffers(1,&VBO);//删除VBO绑定的一个缓存对象
    glDeleteBuffers(1,&EBO);//删除EBO绑定的一个缓存对象
    glDeleteProgram(shaderProgram);//删除着色器程序
    glfwTerminate();//不要忘记释放glfw资源
    return 0;
}
void frame_size_callback(GLFWwindow *window,int width,int height)
{
    glViewport(0,0,width,height);
}
void press_close_window(GLFWwindow *window)
{
    if(glfwGetKey(window,GLFW_KEY_SPACE)==GLFW_PRESS)
        glfwSetWindowShouldClose(window,TRUE);
}