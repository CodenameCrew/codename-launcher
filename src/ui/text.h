#pragma once

#include "raylib.h"
#include "object.h"
#include "global.h"

class Text : public Object
{
    public:
        const char *text;
        float size;
        Color color;
        Font font;
        Text(int x, int y, int width, int height, const char *text, float size = 20.0f, Color color = WHITE, const char* font = DEFAULTFONT);

        void draw();
        void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);
};