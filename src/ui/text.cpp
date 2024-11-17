#include "raylib.h"
#include "object.cpp"

class Text : public Object {
    public:
        char* text;
        float size = 20;
        Color color = WHITE;
        Text(float x, float y, char* text, float size, Color color = WHITE) : Object(x, y, 0, 0) {
            this->text = text;
            this->size = size;
            this->color = color;
        };

        void draw() {
            Object::draw();

            DrawText(TextFormat(text), x, y, size, color);
        };
};