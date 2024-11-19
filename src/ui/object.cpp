#ifndef _OBJECT_CPP_
#define _OBJECT_CPP_

#include "raylib.h"
#include "raymath.h"
#include "global.cpp"
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

        Object(int x, int y, int width, int height) {
            this->x = x;
            this->y = y; 
            this->width = width;
            this->height = height;

            TraceLog(LOG_INFO, TextFormat("made object: {x: %i, y: %i}", this->x, this->y));
        };


        virtual void add(Object* child) {
            children.push_back(child);
        };
        virtual void remove(Object* child) {
            for (int i=0; i<children.size(); i++)
                if (children.at(i) == child)
                    children.erase(children.begin() + i);
        };

        virtual void update(float elapsed) {
            isHovering = GetMousePosition().x == Clamp(GetMousePosition().x, x, x + width) && 
                         GetMousePosition().y == Clamp(GetMousePosition().y, y, y + height);
            for (auto child : children) {
                child->x += x;
                child->y += y;

                child->update(elapsed);
                
                child->x -= x;
                child->y -= y;
            }
        };
        virtual void draw() {
            for (auto child : children) {
                child->x += x;
                child->y += y;

                child->draw();
                
                child->x -= x;
                child->y -= y;
            }

            if (DEBUGMODE) {
                DrawRectangle(x, y, width, height, GetColor(0xff000044));
            }
        };
};
#endif