#include "object.h"

Object::Object(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	TraceLog(LOG_INFO, TextFormat("made object: {x: %0.2f, y: %0.2f}", this->x, this->y));
};

void Object::add(Object *child)
{
	children.push_back(child);
	child->parent = this;
};
void Object::remove(Object *child)
{
	for (auto it = children.begin(); it != children.end(); ++it)
		if (*it == child)
		{
			children.erase(it);
			break;
		}
};

void Object::update(float elapsed)
{
	Vector2 mousePosition = GetMousePosition();

	isHovering = mousePosition.x == Clamp(mousePosition.x, x, x + width) && mousePosition.y == Clamp(mousePosition.y, y, y + height);
	if (parent != nullptr && isHovering && hoverable) parent->isHovering = false;
	for (auto child : children)
	{
		child->x += x;
		child->y += y;

		child->update(elapsed);

		child->x -= x;
		child->y -= y;
	}
};
void Object::draw()
{
	for (auto child : children)
	{
		child->x += x;
		child->y += y;

		child->draw();

		child->x -= x;
		child->y -= y;
	}

	if (DEBUGMODE)
	{
		DrawRectangle(x, y, width, height, GetColor(0xff000044));
	}
};