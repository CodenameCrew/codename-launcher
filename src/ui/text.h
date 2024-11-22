#pragma once

#include "global.h"
#include "object.h"
#include "raylib.h"

class Text : public Object
{
public:
	const char *text;
	float size;
	Color color;
	Font font;
	bool wrap = true;
	Text(
	    int x,
	    int y,
	    int width,
	    int height,
	    const char *text,
	    float size = 20.0f,
	    bool wrap = true,
	    Color color = WHITE,
	    const char *font = DEFAULTFONT
	);

	void draw();
	void DrawTextBoxedSelectable(
	    Font font,
	    const char *text,
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