#include "raylib.h"
#include "raymath.h"
#include "object.cpp"

class Container : public Object {
    public:
        int scroll = 0;
        int scrollMax = 0;
        Container(int x, int y, int width, int height) : Object(x, y, width, height) {
            
        }

        void update(float elapsed) {
            scrollMax = std::max(0, (children.back()->y + children.back()->height) - height);
            scroll = Clamp(scroll - (int)(GetMouseWheelMove()*20), 0, scrollMax);
            TraceLog(LOG_INFO, TextFormat("%i", scroll));

            y -= scroll;
            Object::update(elapsed);
            y += scroll;
        }

        void draw() {
            DrawRectangle(x, y, width, height, color);
            BeginScissorMode(x, y, width, height);

            y -= scroll;
            Object::draw();
            y += scroll;

            EndScissorMode();

            if (scrollMax != 0) {
                DrawRectangleRounded({float(x + width - 5), float(y + scroll), 4, float(height - scrollMax)}, 1.0f, 10, WHITE);
            }
        }
};