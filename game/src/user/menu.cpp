#include "menu.h"
#include "resource_manager.h"
Menu::Menu(int width, int height)
    : start(glm::vec2(width / 2.0f - 292 / 2.0f, height / 4.0f), glm::vec2(292, 106), ResourceManager::getTexture("start")),
      exit(glm::vec2(width / 2.0f - 292 / 2.0f, height / 10.0f), glm::vec2(292, 126), ResourceManager::getTexture("exit")),
      background(ResourceManager::getTexture("menu")),
      logo(ResourceManager::getTexture("logo")),
      backgroundSize(glm::vec2(width, height)), 
      buttonSize(glm::vec2(292, 126)),
      logoSize(glm::vec2(width/2.0f, height/2.0f)),
      logoPos(glm::vec2(width/4.0f,height*0.45f)),
      width(width),height(height){}
Menu::~Menu() {}
void Menu::processInput(float x, float y, bool isPressed)
{
    start.Update(x, y, isPressed);
    exit.Update(x, y, isPressed);
}
void Menu::Draw(SpriteRender &renderer)
{
    static glm::vec2 oldLogoSize=logoSize;
    renderer.DrawSprite(background, glm::vec2(0.0f), backgroundSize);
    logoSize=(float)(sin(3*glfwGetTime())*0.04f+1.0f)*oldLogoSize;
    logoPos.x=width/2.0f-logoSize.x/2.0f;
    renderer.DrawSprite(logo,logoPos,logoSize);
    start.Draw(renderer);
    exit.Draw(renderer);
}