#pragma once

#include "global.h"
#include "object.h"
#include "raylib.h"

class Text : public Object
{
public:
	std::string text;
	float size;
	Color color;
	Font font;
	bool wrap = true;
	Text(
	    int x,
	    int y,
	    int width,
	    int height,
	    std::string text,
	    float size = 20.0f,
	    bool wrap = true,
	    Color color = WHITE,
	    std::string font = DEFAULTFONT
	);

	void draw();
	void DrawTextBoxedSelectable(
	    Font font,
	    std::string text,
	    Rectangle rec,
	    float fontSize,
	    float spacing,
	    bool wordWrap,
	    Color tint,
	    int selectStart,
	    int selectLength,
	    Color selectTint,
	    Color selectBackTint
	);
};