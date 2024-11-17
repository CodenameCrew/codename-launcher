#include "raylib.h"
#include "object.cpp"

class Sprite : public Object {
    public:
        Texture2D texture;
        Sprite(int x, int y, Texture2D texture) : Object(x, y, 0, 0) {
            this->texture = texture;
            width = texture.width;
            height = texture.height;
        };

        void draw() {
            DrawTexture(texture, x, y, color);

            Object::draw();
        }
};