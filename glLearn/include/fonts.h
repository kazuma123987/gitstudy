#ifndef __FONTS__H__
#define __FONTS__H__
#include <tool.h>
#include <shader.h>
struct Character
{
    GLuint TextureID;  // 纹理id
    glm::vec2 Size;    // 字体大小
    glm::vec2 Bearing; // 字体距离原点向右和向下的大小(单位:像素)
    long Advance;      // 当前原点与下一个字符原点的水平距离(//!单位:1/64像素)
};
class Fonts
{
public:
    Fonts(std::vector<std::string> path, glm::vec2 size = glm::vec2(0, 48))
    {
        if (FT_Init_FreeType(&ftlib))
            fputs("\nfailed to init the freetype lib", stderr);
        for (size_t i = 0; i < path.size(); i++)
        {
            FT_Face face = NULL;
            if (FT_New_Face(ftlib, path[i].c_str(), 0, &face))
            {
                fputs("\nfailed to create the freetype face", stderr);
                continue;
            }
            ftface.emplace_back(face);
            FT_Set_Pixel_Sizes(ftface[i], size.x, size.y);
        }
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void *)0); // 定义位置(2)纹理(2)
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    };
    ~Fonts()
    {
        destroy();
    }
    FT_Face getFace(int index = 0)
    {
        return ftface[index];
    }
    void loadChars(int faceIndex = 0)
    {
        if ((size_t)faceIndex >= ftface.size())
        {
            fputs("\nError::over the index of the ftface", stderr);
            return;
        }
        for (unsigned long i = 0; i < 128; i++)
        {
            loadChar(i);
        }
    }
    void loadChar(unsigned long charIndex, int faceIndex = 0)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        if (FT_Load_Char(ftface[faceIndex], charIndex, FT_LOAD_RENDER))
        {
            fputs("\nfailed to load char", stderr);
            return;
        }
        if (isSDF)
        {
            FT_GlyphSlot slot = ftface[faceIndex]->glyph;
            FT_Render_Glyph(slot, FT_RENDER_MODE_SDF);
        }
        else
        {
            FT_Matrix ftMat;
            ftMat.xx = ftMat.yy = 1.0f * 0x10000L;
            ftMat.xy = ftMat.yx = 0.0f * 0x10000L;
            FT_Vector ftVec;
            ftVec.x = ftVec.y = 0.0f * 64; // ftVec的单位为1/64像素,故乘以64
            FT_Set_Transform(ftface[faceIndex], &ftMat, &ftVec);
        }
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, ftface[faceIndex]->glyph->bitmap.width, ftface[faceIndex]->glyph->bitmap.rows, 0,
                     GL_RED, GL_UNSIGNED_BYTE, ftface[faceIndex]->glyph->bitmap.buffer);
        Character ch =
            {
                textureID,
                glm::vec2(ftface[faceIndex]->glyph->bitmap.width, ftface[faceIndex]->glyph->bitmap.rows),
                glm::vec2(ftface[faceIndex]->glyph->bitmap_left, ftface[faceIndex]->glyph->bitmap_top),
                ftface[faceIndex]->glyph->advance.x};
        Characters[charIndex] = ch;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    }
    void destroy()
    {
        for (size_t i = 0; i < ftface.size(); i++)
            FT_Done_Face(ftface[i]);
        FT_Done_FreeType(ftlib);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    void rendText(std::wstring text, glm::vec2 position, float scale = 1.0f)
    {
        glEnable(GL_BLEND);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        float lastX = position.x;
        for (size_t i = 0; i < text.length(); i++)
        {
            unsigned long c = text[i];
            if (Characters.count(c) == 0)
                loadChar(c);
            Character ch = Characters[c];
            if (c == '\n')
            {
                position.x = lastX;
                position.y -= 48 * scale;
            }
            else
            {
                float xPos = position.x + ch.Bearing.x * scale;
                float yPos = position.y - (ch.Size.y - ch.Bearing.y) * scale;
                float w = ch.Size.x * scale;
                float h = ch.Size.y * scale;
                float vertices[] =
                    {
                        xPos, yPos, 0.0f, 1.0f,        // 左下
                        xPos, yPos + h, 0.0f, 0.0f,    // 左上
                        xPos + w, yPos, 1.0f, 1.0f,    // 右下
                        xPos + w, yPos + h, 1.0f, 0.0f // 右上
                    };
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
                position.x += (ch.Advance >> 6) * scale; // 获取以像素为单位的x新坐标
            }
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDisable(GL_BLEND);
    }

private:
    bool isSDF = true;
    FT_Library ftlib;
    std::vector<FT_Face> ftface;
    std::map<unsigned long, Character> Characters;
    GLuint VAO, VBO;
};
#endif