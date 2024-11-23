#pragma once

#include "global.h"
#include "object.h"
#include "raylib.h"

class Text : public Object
{
private:
	std::string text;
public:
	float size;
	Color color;
	Font font;
	bool wrap = true;
	bool autoWidth;
	bool autoHeight;
	Text(
	    int x,
	    int y,
		std::string text,
	    int width = 0,
	    int height = 0,
	    float size = 20.0f,
	    bool wrap = true,
	    Color color = WHITE,
	    std::string font = DEFAULTFONT
	);

	void setText(std::string newText);
	std::string getText() {return text;};
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