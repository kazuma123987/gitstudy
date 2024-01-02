#ifndef __MENU__H
#define __MENU__H
#include "menu_button.h"
class Menu
{
public:
    MenuButton start;
    MenuButton exit;
    Texture background;
    Texture logo;
    glm::vec2 backgroundSize;
    glm::vec2 logoSize;
    glm::vec2 logoPos;
    glm::vec2 buttonSize;
    int width,height;
    Menu(int width,int height);
    ~Menu();
    void processInput(float x,float y,bool isPressed);
    void Draw(SpriteRender &renderer);
};
#endif