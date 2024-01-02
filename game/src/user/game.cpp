#include "game.h"
//*全局变量
const glm::vec2 PLAYER_SIZE(200, 40);
const float PLAYER_VELOCITY = 1000.0f;
const glm::vec2 BALL_VELOCITY(200, 700);
const float BALL_RADIUS = 25.0f;
char FILE_DIR[FILENAME_MAX];
float shakeTime = 0.0f;
SpriteRender *renderer;
ParticleGenerator *particle;
TextRender *textRenderer;
GameObject *player;
BallObject *ball;
PostProcessor *effects;
SoundManager *sound;
Lives *lives;
Menu *menu;
//*函数声明
typedef std::tuple<float, glm::vec2> Collision;
Collision checkCollisions(BallObject &one, GameObject &two);
//*构造函数
Game::Game(int width, int height)
    : state(GAME_MENU), keys(), buttons(), width(width), height(height), curLevel(0), exit(false){};
Game::~Game()
{
    delete renderer;
    delete player;
    delete ball;
    delete particle;
    delete effects;
    delete sound;
    delete textRenderer;
    delete lives;
    delete menu;
};
void Game::Init()
{
    // 初始化随机时间种子
    srand(glfwGetTime());
    // 初始化文件加载路径
    GetCurrentDirectoryA(FILENAME_MAX, FILE_DIR);
    SetCurrentDirectoryA(FILE_DIR);
    // 设置stbi加载为y翻转
    stbi_set_flip_vertically_on_load(true);
    // 加载着色器
    ResourceManager::loadShader("res/shader/sprite.vert", "res/shader/sprite.frag", NULL, "spriteShader");
    ResourceManager::loadShader("res/shader/particle.vert", "res/shader/particle.frag", NULL, "particleShader");
    ResourceManager::loadShader("res/shader/post.vert", "res/shader/post.frag", NULL, "postShader");
    ResourceManager::loadShader("res/shader/text.vert", "res/shader/text.frag", NULL, "textShader");
    // 配置着色器
    glm::mat4 proj = glm::ortho(0.0f, (float)this->width, 0.0f, (float)this->height, -1.0f, 1.0f);
    ResourceManager::getShader("spriteShader").Use().unfm1i("image", 0);
    ResourceManager::getShader("spriteShader").unfmat4("proj", proj);
    ResourceManager::getShader("particleShader").Use().unfm1i("image", 0);
    ResourceManager::getShader("particleShader").unfmat4("proj", proj);
    ResourceManager::getShader("textShader").Use().unfm1i("textImage", 0);
    ResourceManager::getShader("textShader").unfmat4("proj", proj);
    // 创建渲染器
    renderer = new SpriteRender(ResourceManager::getShader("spriteShader"));
    effects = new PostProcessor(ResourceManager::getShader("postShader"), this->width, this->height);
    textRenderer = new TextRender("res/fonts/yolan.ttf", ResourceManager::getShader("textShader"));
    // 加载纹理
    ResourceManager::loadTexture("res/texture/awesomeface.png", GL_UNSIGNED_BYTE, "face");
    ResourceManager::loadTexture("res/texture/block.png", GL_UNSIGNED_BYTE, "block");
    ResourceManager::loadTexture("res/texture/block_solid.png", GL_UNSIGNED_BYTE, "block_solid");
    ResourceManager::loadTexture("res/texture/background.jpg", GL_UNSIGNED_BYTE, "background");
    ResourceManager::loadTexture("res/texture/paddle.png", GL_UNSIGNED_BYTE, "paddle");
    ResourceManager::loadTexture("res/texture/particle.png", GL_UNSIGNED_BYTE, "particle");
    ResourceManager::loadTexture("res/texture/powerup_chaos.png", GL_UNSIGNED_BYTE, "chaos");
    ResourceManager::loadTexture("res/texture/powerup_confuse.png", GL_UNSIGNED_BYTE, "confuse");
    ResourceManager::loadTexture("res/texture/powerup_increase.png", GL_UNSIGNED_BYTE, "increase");
    ResourceManager::loadTexture("res/texture/powerup_passthrough.png", GL_UNSIGNED_BYTE, "passthrough");
    ResourceManager::loadTexture("res/texture/powerup_speed.png", GL_UNSIGNED_BYTE, "speed");
    ResourceManager::loadTexture("res/texture/powerup_sticky.png", GL_UNSIGNED_BYTE, "sticky");
    ResourceManager::loadTexture("res/texture/heart_fill.png", GL_UNSIGNED_BYTE, "heart_fill");
    ResourceManager::loadTexture("res/texture/heart_box.png", GL_UNSIGNED_BYTE, "heart_box");
    ResourceManager::loadTexture("res/texture/menu.png", GL_UNSIGNED_BYTE, "menu");
    ResourceManager::loadTexture("res/texture/startButton.png", GL_UNSIGNED_BYTE, "start");
    ResourceManager::loadTexture("res/texture/exitButton.png", GL_UNSIGNED_BYTE, "exit");
    ResourceManager::loadTexture("res/texture/logo.png", GL_UNSIGNED_BYTE, "logo");
    //创建粒子发射器
    particle = new ParticleGenerator(ResourceManager::getShader("particleShader"), ResourceManager::getTexture("particle"), 800);
    // 加载存档
    loadSaves("res/saves/0.data");
    // 加载关卡
    for (int i = 1; i <= 4; i++)
    {
        GameLevel level;
        level.Load(("res/level/level" + std::to_string(i)).c_str(), this->width, this->height);
        this->levels.emplace_back(level);
    }
    // 创建玩家物体
    glm::vec2 playerPos(this->width / 2.0f - PLAYER_SIZE.x / 2.0f, 0.0f);
    player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::getTexture("paddle"));
    // 创建球物体
    glm::vec2 ballPos(playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, PLAYER_SIZE.y));
    ball = new BallObject(ballPos, BALL_RADIUS, BALL_VELOCITY, ResourceManager::getTexture("face"));
    // 创建生命值
    lives = new Lives(this->width, this->height, 3, 50);
    // 创建菜单界面
    menu = new Menu(this->width, this->height);
    // 创建音频管理器
    sound = new SoundManager(32);
    // 加载音乐
    sound->loadSound("res/music/game_active.mp3", "game_active", FMOD_LOOP_NORMAL);
    sound->loadSound("res/music/menu.mp3", "menu", FMOD_LOOP_NORMAL);
    sound->loadSound("res/music/brick_hit.mp3", "brick_hit");
    sound->loadSound("res/music/paddle_hit.mp3", "paddle_hit");
    sound->loadSound("res/music/solid_hit.wav", "solid_hit");
    sound->loadSound("res/music/powerup.wav", "powerup");
    sound->loadSound("res/music/devil.mp3", "devil");
    sound->loadSound("res/music/lose.mp3", "lose");
    sound->loadSound("res/music/win.mp3", "win");
    sound->loadSound("res/music/button.wav", "button");
    // 播放游戏菜单音乐
    sound->playSound("menu", 0);
};
void Game::ProcessInput(float deltaTime)
{
    if (this->state == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * deltaTime;
        if (this->keys[GLFW_KEY_A])
        {
            if (player->position.x >= -player->size.x)
            {
                player->position.x -= velocity;
                player->velocity.x = -PLAYER_VELOCITY;
            }
            if (ball->stuck)
                ball->position.x -= velocity;
        }
        if (this->keys[GLFW_KEY_D])
        {
            if (player->position.x <= this->width)
            {
                player->position.x += velocity;
                player->velocity.x = PLAYER_VELOCITY;
            }
            if (ball->stuck)
                ball->position.x += velocity;
        }
        if (!this->keys[GLFW_KEY_A] && !this->keys[GLFW_KEY_D])
            player->velocity.x = 0;
        if (this->keys[GLFW_KEY_SPACE])
            ball->stuck = false;
    }
    else if (this->state == GAME_MENU)
    {
        menu->processInput(cursorPos.x, cursorPos.y, buttons[GLFW_MOUSE_BUTTON_LEFT]);
    }
    else if (this->state == GAME_WIN)
    {
        static float timer = 0.0f;
        timer += deltaTime;
        if (timer >= 2.0f)
        {
            timer = 0.0f;
            this->state = GAME_MENU;
            curLevel = (curLevel + 1) % 4;
            writeSaves("res/saves/0.data");
            this->resetLevel();
            sound->stopGroup(0);
            sound->playSound("menu", 0);
        }
    }
    else if (this->state == GAME_LOSE)
    {
        static float timer = 0.0f;
        timer += deltaTime;
        if (timer >= 2.0f)
        {
            timer = 0.0f;
            this->state = GAME_MENU;
            sound->stopGroup(0);
            sound->playSound("menu", 0);
        }
    }
};
void Game::Update(float deltaTime)
{
    // 更新音乐管理器
    sound->update();
    if (this->state == GAME_ACTIVE)
    {
        // 球的移动
        ball->Move(deltaTime, this->width, this->height);
        // 碰撞检测
        this->doCollisions();
        // 更新粒子
        particle->Update(deltaTime, *ball, 4, ball->size / 4.0f);
        // 更新特效时间
        if (shakeTime > 0.0f)
        {
            shakeTime -= deltaTime;
            if (shakeTime <= 0.0f)
                effects->shake = false;
        }
        // 检测是否失败
        if (ball->position.y <= -ball->size.y)
        {
            lives->curLifePoint--;
            if (lives->curLifePoint == 0)
            {
                this->state = GAME_LOSE;
                textRenderer->RenderText(L"YOU LOSE", glm::vec2(600, 450), 1.5f, glm::vec3(1.0f, 0.0f, 0.0f));
                sound->stopGroup(0);
                sound->playSound("lose", 0);
                this->resetLevel();
            }
            this->resetPlayer();
        }
        // 检测是否胜利
        if (this->isCompleted())
        {
            this->resetPlayer();
            this->state = GAME_WIN;
            textRenderer->RenderText(L"YOU WIN", glm::vec2(600, 450), 1.5f, glm::vec3(0.0f, 0.5f, 0.8f));
            sound->stopGroup(0);
            sound->playSound("win", 0);
        }
        // 更新道具powerUps(必须最后更新)
        updatePowerUps(deltaTime);
    }
    else if (this->state == GAME_MENU)
    {
        if (menu->start.click)
        {
            this->state = GAME_ACTIVE;
            menu->start.click = false;
            sound->playSound("button", 1);
            sound->stopGroup(0);
            sound->playSound("game_active", 0);
        }
        else if (menu->exit.click)
        {
            this->exit = true;
            writeSaves("res/saves/0.data");//保存存档
        }
    }
};
void Game::Render()
{
    if (this->state == GAME_ACTIVE)
    {
        // 先绑定帧缓冲
        effects->BindMFBO();
        //  绘制背景(最先绘制)
        renderer->DrawSprite(ResourceManager::getTexture("background"), glm::vec2(0, 0), glm::vec2(this->width, this->height));
        // 绘制关卡
        this->levels[this->curLevel].Draw(*renderer);
        // 绘制玩家
        player->Draw(*renderer);
        // 绘制粒子(球前面绘制)
        particle->Draw();
        // 绘制球
        ball->Draw(*renderer);
        // 绘制道具powerUp
        for (size_t i = 0; i < powerUps.size(); i++)
        {
            if (!powerUps[i].destoryed)
                powerUps[i].Draw(*renderer);
        }
        // 绘制特效
        effects->Copy_MFBO_To_FBO();
        effects->Draw();
        // 绘制生命值
        lives->Draw(*renderer);
        // 绘制关卡数
        textRenderer->RenderText(L"Level:" + std::to_wstring(this->curLevel + 1), glm::vec2(700, 850),1.0f,glm::vec3(0.8f,0.8f,0.1f));
    }
    else if (this->state == GAME_MENU)
    {
        menu->Draw(*renderer);
    }
};
Collision checkCollisions(BallObject &one, GameObject &two)
{
    // 计算球的中心、aabb物体的半边长、aabb的中心
    glm::vec2 ball_center = one.position + one.radius;
    glm::vec2 aabb_half_extents(two.size / 2.0f);
    glm::vec2 aabb_center = two.position + aabb_half_extents;
    // 计算两物体中心矢量差和离球心最近的aabb上的点
    glm::vec2 ballDir = ball_center - aabb_center;
    glm::vec2 closestDir = glm::clamp(ballDir, -aabb_half_extents, aabb_half_extents);
    glm::vec2 closest = closestDir + aabb_center;
    glm::vec2 diff = ball_center - closest; // 最近点指向圆心
    // 计算球心到最近点的距离是否小于半径
    return std::make_tuple(glm::length(diff), diff);
}
bool checkCollisions(GameObject &one, GameObject &two)
{
    bool xCheck = false, yCheck = false;
    if (one.position.x + one.size.x >= two.position.x && two.position.x + two.size.x >= one.position.x)
        xCheck = true;
    if (one.position.y + one.size.y >= two.position.y && two.position.y + two.size.y >= one.position.y)
        yCheck = true;
    return xCheck & yCheck;
}
void Game::doCollisions()
{
    bool dirHasChanged = false; // 在每一帧里面只许改变一次方向(撞到多个物体时)
    //*球与砖块的碰撞检测
    for (GameObject &brick : this->levels[curLevel].bricks)
    {
        if (!brick.destoryed)
        {
            Collision collision = checkCollisions(*ball, brick);
            float length = std::get<0>(collision);
            glm::vec2 diff = std::get<1>(collision);
            if (length <= ball->radius)
            {
                if (!brick.isSolid)
                {
                    sound->playSound("brick_hit", 1);
                    brick.destoryed = true;
                    spawnPowerUps(brick); // 销毁时有概率生成道具
                }
                else if (!ball->passThrough)
                {
                    sound->playSound("solid_hit", 1);
                    shakeTime = 0.05f;
                    effects->shake = true;
                }
                // 先进行速度更新
                if (!ball->passThrough || !brick.isSolid) // 当ball又能穿墙砖块又是固体时不进行位置和速度更新
                {
                    if (!dirHasChanged) // 如果没在该帧中改变过方向才进行判断
                    {
                        dirHasChanged = true;
                        if (abs(diff.x) > 0)
                            ball->velocity.x = -ball->velocity.x;
                        if (abs(diff.y) > 0)
                            ball->velocity.y = -ball->velocity.y;
                        if (length)
                            ball->position += ((ball->radius - length) * glm::normalize(diff));
                        else
                            ball->position.y -= brick.size.y + ball->size.y;
                    }
                }
            }
        }
        //*球与玩家的碰撞检测
        if (!ball->stuck)
        {
            Collision collision = checkCollisions(*ball, *player);
            float length = std::get<0>(collision);
            glm::vec2 diff = std::get<1>(collision);
            if (length <= ball->radius)
            {
                // 先进行速度更新
                if (!dirHasChanged)
                {
                    sound->playSound("paddle_hit", 1);
                    float oldBallVelocity = glm::length(ball->velocity);
                    float max_x = abs(ball->velocity.y * 1.73f);
                    ball->velocity.x += player->velocity.x * 0.1f;
                    if (ball->velocity.x > max_x)
                        ball->velocity.x = max_x;
                    else if (ball->velocity.x < -max_x)
                        ball->velocity.x = -max_x;
                    ball->velocity.y = abs(ball->velocity.y);
                    ball->velocity = oldBallVelocity * glm::normalize(ball->velocity);
                    dirHasChanged = true;
                    // 再进行位置复原
                    if (length)
                        ball->position += (ball->radius - length) * glm::normalize(diff);
                    else
                        ball->position.y = player->size.y;
                    ball->stuck = ball->sticky; // 仅碰撞时更新stuck
                }
            }
        }
        //*powerUp道具与玩家的碰撞
        for (PowerUp &powerUp : this->powerUps)
        {
            if (!powerUp.destoryed)
            {
                // 如果落到地面会被销毁
                if (powerUp.position.y <= -powerUp.size.y)
                    powerUp.destoryed = true;
                // 如果碰到玩家会被销毁且激活
                if (checkCollisions(*player, powerUp))
                {
                    sound->playSound("powerup", 1);
                    powerUp.destoryed = true;
                    activatePowerUp(powerUp);
                }
            }
        }
    }
}
void Game::resetLevel()
{
    lives->curLifePoint = 3;
    this->levels[curLevel].Load(("res/level/level" + std::to_string(curLevel + 1)).c_str(), this->width, this->height);
    for (auto &powerUp : this->powerUps)
    {
        powerUp.duration = 0.0f;
        powerUpTimer[powerUp.type] = 0.0f;
        powerUp.destoryed = true;
    }
}
void Game::resetPlayer()
{
    player->size = PLAYER_SIZE;
    player->position = glm::vec2((this->width - player->size.x) / 2.0f, 0.0f);
    player->color = glm::vec3(1.0f);
    ball->Reset(player->position + glm::vec2(player->size.x / 2.0f - ball->size.x / 2.0f, player->size.y), BALL_VELOCITY);
}
void Game::spawnPowerUps(GameObject &brick)
{
    if (randBool(40))
        this->powerUps.emplace_back(
            PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 20.0f, brick.position, ResourceManager::getTexture("speed")));
    else if (randBool(40))
        this->powerUps.emplace_back(
            PowerUp("increase", glm::vec3(1.0f, 0.6f, 0.4), 40.0f, brick.position, ResourceManager::getTexture("increase")));
    else if (randBool(40))
        this->powerUps.emplace_back(
            PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 18.0f, brick.position, ResourceManager::getTexture("sticky")));
    else if (randBool(40))
        this->powerUps.emplace_back(
            PowerUp("passthrough", glm::vec3(0.5f, 1.0f, 0.5f), 30.0f, brick.position, ResourceManager::getTexture("passthrough")));
    else if (randBool(15)) // 负面道具被更频繁地生成
        this->powerUps.emplace_back(
            PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 8.0f, brick.position, ResourceManager::getTexture("confuse")));
    else if (randBool(15))
        this->powerUps.emplace_back(
            PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 6.0f, brick.position, ResourceManager::getTexture("chaos")));
}
void Game::updatePowerUps(float deltaTime)
{
    for (PowerUp &powerUp : powerUps)
    {
        powerUp.position += powerUp.velocity * deltaTime;
        if (powerUp.activated) // 仅激活时计算效果时间
        {
            powerUp.duration -= deltaTime;
            powerUpTimer[powerUp.type] -= deltaTime; // 效果计时器(对speed和increase效果不生效)
            if (powerUp.duration <= 0.0)
            {
                // 禁用激活
                powerUp.activated = false;
                // 恢复原状态
                if (powerUp.type == "speed")
                {
                    if (powerUpTimer["speed"] <= 0.0f)
                    {
                        ball->velocity = BALL_VELOCITY;
                    }
                }
                else if (powerUp.type == "increase")
                {
                    if (powerUpTimer["increase"] <= 0.0f)
                    {
                        player->size.x = PLAYER_SIZE.x;
                    }
                }
                else if (powerUp.type == "sticky")
                {
                    if (powerUpTimer["sticky"] <= 0.0f)
                    {
                        ball->sticky = false;
                        player->color = glm::vec3(1.0f);
                    }
                }
                else if (powerUp.type == "passthrough")
                {
                    if (powerUpTimer["passthrough"] <= 0.0f)
                    {
                        ball->passThrough = false;
                        ball->color = glm::vec3(1.0f);
                    }
                }
                else if (powerUp.type == "confuse")
                {
                    if (powerUpTimer["confuse"] <= 0.0f)
                    {
                        effects->confuse = false;
                    }
                }
                else if (powerUp.type == "chaos")
                {
                    if (powerUpTimer["chaos"] <= 0.0f)
                    {
                        effects->chaos = false;
                    }
                }
            }
        }
        // 取得满足删除条件的迭代器
        auto removeItems = std::remove_if(this->powerUps.begin(), this->powerUps.end(),
                                          [](const PowerUp &powerUp)
                                          { return powerUp.destoryed && !powerUp.activated; });
        // 移除元素
        this->powerUps.erase(removeItems, this->powerUps.end());
    }
}
void Game::activatePowerUp(PowerUp &powerUp)
{
    powerUp.activated = true;
    // 根据类型发动效果
    if (powerUp.type == "speed")
    {
        ball->velocity *= 1.2f;
        this->powerUpTimer["speed"] = 20.0f;
    }
    else if (powerUp.type == "increase")
    {
        player->size.x *= 1.5f;
        this->powerUpTimer["increase"] = 40.0f;
    }
    else if (powerUp.type == "sticky")
    {
        ball->sticky = true;
        player->color = powerUp.color;
        this->powerUpTimer["sticky"] = 18.0f;
    }
    else if (powerUp.type == "passthrough")
    {
        ball->passThrough = true;
        ball->color = powerUp.color;
        this->powerUpTimer["passthrough"] = 30.0f;
    }
    else if (powerUp.type == "confuse")
    {
        if (!effects->chaos)
        {
            effects->confuse = true;
            this->powerUpTimer["confuse"] = 8.0f;
        }
    }
    else if (powerUp.type == "chaos")
    {
        if (!effects->confuse)
        {
            effects->chaos = true;
            this->powerUpTimer["chaos"] = 6.0f;
            sound->playSound("devil", 0);
        }
    }
}
bool Game::isCompleted()
{
    for (auto &brick : this->levels[curLevel].bricks)
    {
        if (!brick.isSolid && !brick.destoryed)
            return false;
    }
    return true;
}
void Game::loadSaves(const char* path)
{
    FILE *fp = NULL;
    fopen_s(&fp, path, "rb");
    if (fp == NULL)
    {
        printf("failed to open the file\n");
        return;
    }
    fseek(fp, 0, SEEK_END);
    size_t textSize = ftell(fp);
    char *text = (char *)malloc(textSize + 1);
    rewind(fp);
    fread(text, sizeof(char), textSize, fp);
    if (text)
    {
        char *ptr = text;
        char numBuffer[12];
        int bufferIndex = 0;
        while (true)
        {
            if (*ptr >= '0' && *ptr <= '9')
                numBuffer[bufferIndex++] = *ptr;
            ptr++;
            if (*ptr == '\n' || *ptr == '\0' || *ptr == ' ')
            {
                numBuffer[bufferIndex] = '\0';
                this->curLevel = atoi(numBuffer);
                break;
            }
        }
    }
    free(text);
    fclose(fp);
}
void Game::writeSaves(const char* path)
{
    FILE *fp = NULL;
    fopen_s(&fp, path, "w");
    fprintf(fp, "%d", this->curLevel);
    fclose(fp);
}