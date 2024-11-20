#include "button.h"

extern Vector2 mousePosition;

Button::Button(int x, int y, int width, int height, Color color) : Object(x, y, width, height) {
    this->color = color;
};

void Button::update(float elapsed) {
    Object::update(elapsed);

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

void Button::draw() {
    DrawRectangle(x, y, width, height, ColorBrightness(color, tint));
    DrawRectangleLinesEx({float(x), float(y), float(width), float(height)}, 2, GetColor(0x00000033));

    Object::draw();
};