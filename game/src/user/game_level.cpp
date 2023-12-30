#include "game_level.h"
void GameLevel::Load(const char *path, int width, int height)
{
    this->bricks.clear();
    std::vector<std::vector<int>> tileData;
    char *data = ResourceManager::loadText(path);
    char *ptr = data;
    while (*ptr != '\0')
    {
        std::vector<int> idata;
        for (; *ptr != '\n' && *ptr != '\0'; ptr++)
        {
            if (*ptr >= '0' && *ptr <= '9')
                idata.push_back(*ptr - '0');
        }
        tileData.push_back(idata);
        if (*ptr != '\0')
            ptr++;
    }
    free(data);
    Init(tileData, width, height);
}
void GameLevel::Draw(SpriteRender &renderer)
{
    for (size_t i = 0; i < bricks.size(); i++)
        if (!bricks[i].destoryed)
            bricks[i].Draw(renderer);
}
bool GameLevel::IsCompleted()
{
    for (size_t i = 0; i < bricks.size(); i++)
        if (!bricks[i].isSolid && !bricks[i].destoryed)
            return false;
    return true;
}
void GameLevel::Init(std::vector<std::vector<int>> tileData, int width, int height)
{
    size_t w_num = tileData[0].size();
    size_t h_num = tileData.size();
    float unitWidth = width / (float)w_num;
    float unitHeight = height / (float)(h_num*2);
    for (int i = 0; i < h_num; i++)
        for (int j = 0; j < w_num; j++)
        {
            if (tileData[i][j] == 1)
            {
                glm::vec2 pos(unitWidth * j, height - unitHeight * (i + 1));
                GameObject obj(pos, glm::vec2(unitWidth, unitHeight), ResourceManager::getTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
                obj.isSolid = true;
                bricks.emplace_back(obj);
            }
            else if (tileData[i][j] > 1)
            {
                glm::vec3 color;
                if (tileData[i][j] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[i][j] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[i][j] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[i][j] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);
                glm::vec2 pos(unitWidth * j, height - unitHeight * (i + 1));
                GameObject obj(pos, glm::vec2(unitWidth, unitHeight), ResourceManager::getTexture("block"), color);
                bricks.emplace_back(obj);
            }
        }
}