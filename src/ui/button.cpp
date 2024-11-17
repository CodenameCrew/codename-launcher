#include "raylib.h"
#include "object.cpp"
#include "raymath.h" 

extern Vector2 mousePosition;

class Button : public Object{
    public:
        virtual void clickCallback() = 0;
        bool isHovering = false;

        float tint = 0.0f;

        Button(int x, int y, int width, int height, Color color) : Object(x, y, width, height) {

            this->color = color;
        };

        void update(float elapsed) {
            Object::update(elapsed);

            isHovering = GetMousePosition().x == Clamp(GetMousePosition().x, x, x + width) && 
                         GetMousePosition().y == Clamp(GetMousePosition().y, y, y + height);

            if (isHovering) {
                tint = 0.4f;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    tint = -0.4f;
                }
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    if (clickCallback != 0) clickCallback();
                }
            }
            else tint = 0.0f;
        };

        void draw() {
            DrawRectangle(x, y, width, height, ColorBrightness(color, tint));
            DrawRectangleLinesEx({float(x), float(y), float(width), float(height)}, 2, GetColor(0x00000033));

            Object::draw();
        };
};