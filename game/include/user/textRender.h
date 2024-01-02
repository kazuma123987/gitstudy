#ifndef __TEXTRENDER__H
#define __TEXTRENDER__H
#include <vector>
#include <map>
#include <stringapiset.h>
#include "ft2build.h"
#include FT_FREETYPE_H
#include "shader.h"
struct Character
{
    GLuint TextureID;  // 纹理id
    glm::vec2 Size;    // 字体大小(单位:像素)
    glm::vec2 Bearing; // 字体距离原点向右和向下的大小(单位:像素)
    long Advance;      // 当前原点与下一个字符原点的水平距离(//!单位:1/64像素)
};
class TextRender
{
public:
    TextRender(std::string fontPath, Shader &shader,glm::vec2 fontSize = glm::vec2(0,48));
    ~TextRender();
    void utf8_to_wchar(wchar_t *dstBuffer, size_t bufferSize, char *src);
    void RenderText(std::wstring text, glm::vec2 position, float scale = 1.0f, glm::vec3 color = glm::vec3(1.0f),int faceIndex=0);
    void loadFont(std::string fontPath, glm::vec2 fontSize = glm::vec2(0,48));

private:
    FT_Library lib;
    std::vector<FT_Face> faces;
    std::map<unsigned long, Character> chars;
    GLuint VAO, VBO;
    Shader shader;
    void loadChar(unsigned long charName, int faceIndex = 0);
    void destory();
};
#endif