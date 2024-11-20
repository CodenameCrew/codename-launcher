#include "raylib.h"
#include "raymath.h"
#include "object.h"
#include "global.h"
#include <vector>

Object::Object(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

	TraceLog(LOG_INFO, TextFormat("made object: {x: %i, y: %i}", this->x, this->y));
};

void Object::add(Object* child) {
    children.push_back(child);
};
void Object::remove(Object* child) {
    for (int i=0; i<children.size(); i++)
        if (children.at(i) == child)
            children.erase(children.begin() + i);
};

void Object::update(float elapsed) {
	Vector2 mousePosition = GetMousePosition();

    isHovering = mousePosition.x == Clamp(mousePosition.x, x, x + width) &&
                 mousePosition.y == Clamp(mousePosition.y, y, y + height);
    for (auto child : children) {
        child->x += x;
        child->y += y;

        child->update(elapsed);

        child->x -= x;
        child->y -= y;
    }
};
void Object::draw() {
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