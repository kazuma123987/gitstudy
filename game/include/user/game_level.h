#ifndef __GAME__LEVEL__H
#define __GAME__LEVEL__H
#include <vector>
#include "game_object.h"
#include "resource_manager.h"
class GameLevel
{
public:
    std::vector<GameObject> bricks; // 砖块
    GameLevel(){};
    void Load(const char *path, int width, int height);
    void Draw(SpriteRender &renderer);
    bool IsCompleted();
private:
    void Init(std::vector<std::vector<int>> tileData,int width,int height);
};
#endif