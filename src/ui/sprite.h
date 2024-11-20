#pragma once

#include "raylib.h"
#include "object.h"

class Sprite : public Object {
    public:
        Texture2D texture;
        Sprite(int x, int y, Texture2D texture);

        void draw();
};