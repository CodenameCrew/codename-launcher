#pragma once

#include "raylib.h"
#include "raymath.h"
#include "global.h"
#include <vector>

class Object {
    public:
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;

        Color color = {255, 255, 255, 255};

        std::vector<Object*> children;

        bool isHovering = false;

        Object(int x, int y, int width, int height);

        virtual void add(Object* child);
        virtual void remove(Object* child);

        virtual void update(float elapsed);
        virtual void draw();
};