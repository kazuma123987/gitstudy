#include "button.h"
Button::Button(glm::vec2 position, glm::vec2 size, Texture &texture)
    : position(position), size(size), texture(texture), status(Button_Idle) {}
Button::~Button() {}
void Button::Update(float x, float y, bool isPressed)
{
    if (this->status == Button_Idle)
    {
        if (checkCursor(x, y))
            this->status = Button_Hovered;
    }
    else if (this->status == Button_Hovered)
    {
        if (checkCursor(x, y))
        {
            if (isPressed)
                this->status = Button_Pushed;
        }
        else
            this->status = Button_Idle;
    }
    else if (this->status = Button_Pushed)
    {
        if (!isPressed)
        {
            OnClick();
            this->status = Button_Hovered;
        }
    }
}
void Button::Draw(SpriteRender &renderer)
{
    switch (this->status)
    {
    case Button_Idle:
        renderer.DrawSprite(texture, position, size, 0.0f, glm::vec3(1.0f), 1.0f);
        break;
    case Button_Hovered:
        renderer.DrawSprite(texture, position, size, 0.0f, glm::vec3(1.0f), 0.5f);
        break;
    case Button_Pushed:
        renderer.DrawSprite(texture, position, size, 0.0f, glm::vec3(1.0f), 1.5f);
        break;
    default:
        break;
    }
}
bool Button::checkCursor(float x, float y)
{
    return x > position.x && x < position.x + size.x && y > position.y && y < position.y + size.y;
}