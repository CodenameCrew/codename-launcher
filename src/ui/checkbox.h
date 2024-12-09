#pragma once

#include "button.h"
#include "raylib.h"
class Checkbox : public Button
{
public:
	Color blankColor;
	bool isChecked = true;

	Checkbox(float x, float y, float width, float height, Color color, Color blankColor);

	void draw();

	void click();
};