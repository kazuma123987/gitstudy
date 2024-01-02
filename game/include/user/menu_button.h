#ifndef __MENU__BUTTON__H
#define __MENU__BUTTON__H
#include "button.h"
class MenuButton : public Button
{
public:
    bool click;
    MenuButton(glm::vec2 position, glm::vec2 size, Texture &texture) : Button(position, size, texture), click(false) {}
    ~MenuButton(){};

protected:
    void OnClick()
    {
        this->click = true;
    }
};
#endif