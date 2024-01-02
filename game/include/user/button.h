#ifndef __BUTTON__H
#define __BUTTON__H
#include "sprite_render.h"
enum Button_Status
{
    Button_Idle,
    Button_Hovered,
    Button_Pushed
};
class Button
{
public:
    glm::vec2 position, size;
    Button_Status status;
    Button(glm::vec2 position, glm::vec2 size, Texture &texture);
    ~Button();
    void Update(float x, float y, bool isPressed);
    void Draw(SpriteRender &renderer);

protected:
    virtual void OnClick() = 0;

private:
    Texture texture;
    bool checkCursor(float x, float y);
};
#endif