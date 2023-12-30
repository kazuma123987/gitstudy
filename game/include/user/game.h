#ifndef __GAME__H
#define __GAME__H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <algorithm>
#include "sprite_render.h"
#include "resource_manager.h"
#include "game_level.h"
#include "ball_object.h"
#include "particle_generator.h"
#include "post_processor.h"
#include "PowerUp.h"
enum GameState
{
    GAME_MENU,
    GAME_ACTIVE,
    GAME_WIN
};
class Game
{
public:
    GameState state;
    bool keys[1024];
    int width, height;
    std::vector<GameLevel> levels;
    std::vector<PowerUp> powerUps;
    std::unordered_map<std::string,float> powerUpTimer;
    int curLevel;
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
};
#endif