#include "container.h"
#include <typeinfo>

Container::Container(float x, float y, float width, float height) : Object(x, y, width, height)
{
	hoverable = true;
}

void Container::update(float elapsed)
{
	Vector2 mousePosition = GetMousePosition();

	isHovering = mousePosition.x == Clamp(mousePosition.x, x, x + width) && mousePosition.y == Clamp(mousePosition.y, y, y + height);

	if (!children.empty())
	{
		Object *lastChild = children.back();
		scrollMax = std::max(0.0f, (lastChild->y + lastChild->height) - height);
		if (isHovering)
			scroll = Clamp(scroll - (int)(GetMouseWheelMove() * 20), 0, scrollMax);
		// TraceLog(LOG_INFO, TextFormat("%i", scroll));
	}
	else
		scrollMax = 0;

	y -= scroll;
	Object::update(elapsed);
	y += scroll;
}

void Container::draw()
{
	BeginScissorMode((int)x, (int)y, (int)width, (int)height);

	y -= scroll;
	Object::draw();
	y += scroll;

	EndScissorMode();

	if (scrollMax != 0)
	{
		DrawRectangleRounded(Rectangle{x + width - 5, y + scroll, 4, height - scrollMax}, 1.0f, 10, WHITE);
	}
}