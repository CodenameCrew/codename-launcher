#include "container.h"

Container::Container(int x, int y, int width, int height) : Object(x, y, width, height) {
    // nothing ig
}

void Container::update(float elapsed) {
    Vector2 mousePosition = GetMousePosition();

    isHovering = mousePosition.x == Clamp(mousePosition.x, x, x + width) &&
                 mousePosition.y == Clamp(mousePosition.y, y, y + height);

    scrollMax = std::max(0, (children.back()->y + children.back()->height) - height);
    if (isHovering) scroll = Clamp(scroll - (int)(GetMouseWheelMove()*20), 0, scrollMax);
    //TraceLog(LOG_INFO, TextFormat("%i", scroll));

    y -= scroll;
    Object::update(elapsed);
    y += scroll;
}

void Container::draw() {
    BeginScissorMode(x, y, width, height);

    y -= scroll;
    Object::draw();
    y += scroll;

    EndScissorMode();

    if (scrollMax != 0) {
        DrawRectangleRounded({float(x + width - 5), float(y + scroll), 4, float(height - scrollMax)}, 1.0f, 10, WHITE);
    }
}