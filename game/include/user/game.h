#ifndef __GAME__H
#define __GAME__H
#include <windows.h>
#include <algorithm>
#include "sprite_render.h"
#include "resource_manager.h"
#include "game_level.h"
#include "ball_object.h"
#include "particle_generator.h"
#include "post_processor.h"
#include "PowerUp.h"
#include "sound_manager.h"
#include "textRender.h"
#include "lives.h"
#include "menu.h"
enum GameState
{
    GAME_MENU,
    GAME_ACTIVE,
    GAME_WIN,
    GAME_LOSE
};
class Game
{
public:
    GameState state;                                     // 游戏状态
    bool keys[1024];                                     // 游戏按键
    bool buttons[8];
    int width, height;                                   // 游戏界面宽高
    std::vector<GameLevel> levels;                       // 关卡
    int curLevel;                                        // 当前关卡
    std::vector<PowerUp> powerUps;                       // 道具
    std::unordered_map<std::string, float> powerUpTimer; // 道具效果计时器
    glm::vec2 cursorPos;                                 // 鼠标位置
    bool exit;
    Game(int width, int height);
    ~Game();
    void Init();
    void ProcessInput(float deltaTime);
    void Update(float deltaTime);
    void Render();

private:
    void doCollisions();
    void resetLevel();
    void resetPlayer();
    void spawnPowerUps(GameObject &brick);
    void updatePowerUps(float deltaTime);
    inline bool randBool(int chance) // 1/chance的概率为true
    {
        return (chance != 0) ? (rand() % chance == 0) : false;
    };
    void activatePowerUp(PowerUp &powerUp);
    bool isCompleted();
    void loadSaves(const char* path);
    void writeSaves(const char* path);
};
#endif