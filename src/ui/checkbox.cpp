#include <ui/checkbox.h>

Checkbox::Checkbox(float x, float y, float width, float height, Color color, Color blankColor) : Button(x, y, width, height, color)
{
	this->blankColor = blankColor;
	// nothing else ig
}

void Checkbox::click()
{
	isChecked = !isChecked;

	Button::click();
}

void Checkbox::draw()
{
	DrawRectangleRec(Rectangle{x, y, width, height}, ColorBrightness(isChecked ? color : blankColor, tint));
	DrawRectangleLinesEx(Rectangle{x, y, width, height}, 2, GetColor(0x00000033));

	Object::draw();
}