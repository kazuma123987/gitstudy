#include "textRender.h"
TextRender::TextRender(std::string fontPath, Shader &shader, glm::vec2 fontSize) : shader(shader)
{
    if (FT_Init_FreeType(&this->lib))
        printf("failed to init freetype\n");
    loadFont(fontPath, fontSize);
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glBindVertexArray(0);
}
TextRender::~TextRender()
{
    destory();
}
void TextRender::utf8_to_wchar(wchar_t *dstBuffer, size_t bufferSize, char *src)
{
    size_t srcSize = strlen(src);
    size_t w_size = MultiByteToWideChar(CP_UTF8, 0, src, srcSize, NULL, 0);
    if (w_size > bufferSize)
    {
        printf("utf8_to_wchar error::out of the dst buffer\n");
        return;
    }
    MultiByteToWideChar(CP_UTF8, 0, src, srcSize, dstBuffer, w_size);
    dstBuffer[w_size] = L'\0';
}
void TextRender::RenderText(std::wstring text, glm::vec2 position, float scale, glm::vec3 color, int faceIndex)
{
    shader.Use();
    shader.unfvec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    float lastX = position.x;
    for (size_t i = 0; i < text.size(); i++)
    {
        unsigned long c = text[i];
        if (chars.count(c) == 0)
            loadChar(c, faceIndex);
        Character ch = chars[c];
        if (c == '\n')
        {
            position.x = lastX;
            position.y -= 48.0f;
        }
        else
        {
            float xPos = position.x + ch.Bearing.x * scale;
            float yPos = position.y - (ch.Size.y - ch.Bearing.y) * scale;
            float xSize = ch.Size.x * scale;
            float ySize = ch.Size.y * scale;
            //注意因为freetype纹理坐标与opengl上下颠倒,需要把opengl坐标变为上下颠倒以适应
            float vertices[] =
                {
                    xPos, yPos, 0.0f, 1.0f,                // 左下
                    xPos + xSize, yPos, 1.0f, 1.0f,        // 右下
                    xPos, yPos + ySize, 0.0f, 0.0f,        // 左上
                    xPos + xSize, yPos + ySize, 1.0f, 0.0f // 右上
                };
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            position.x += (ch.Advance >> 6) * scale;
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void TextRender::loadFont(std::string fontPath, glm::vec2 fontSize)
{
    FT_Face face = NULL;
    if (FT_New_Face(this->lib, fontPath.c_str(), 0, &face))
        printf("failed to load font from:%s\n", fontPath.c_str());
    faces.emplace_back(face);
    FT_Set_Pixel_Sizes(faces[faces.size() - 1], fontSize.x, fontSize.y);
}
void TextRender::loadChar(unsigned long charName, int faceIndex)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    if (FT_Load_Char(faces[faceIndex], charName, FT_LOAD_RENDER))
    {
        printf("failed to load char %c\n", charName);
        return;
    }
    FT_Render_Glyph(faces[faceIndex]->glyph, FT_RENDER_MODE_SDF);
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, faces[faceIndex]->glyph->bitmap.width, faces[faceIndex]->glyph->bitmap.rows,
                 0, GL_RED, GL_UNSIGNED_BYTE, faces[faceIndex]->glyph->bitmap.buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    this->chars[charName] = {
        textureID,
        glm::vec2(faces[faceIndex]->glyph->bitmap.width, faces[faceIndex]->glyph->bitmap.rows),
        glm::vec2(faces[faceIndex]->glyph->bitmap_left, faces[faceIndex]->glyph->bitmap_top),
        faces[faceIndex]->glyph->advance.x};
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}
void TextRender::destory()
{
    for (size_t i = 0; i < faces.size(); i++)
        FT_Done_Face(faces[i]);
    FT_Done_FreeType(this->lib);
    glDeleteBuffers(1, &this->VBO);
    glDeleteVertexArrays(1, &this->VAO);
}