#pragma once

#include "object.h"
#include "raylib.h"
#include "raymath.h"
#include <functional>

class Button : public Object
{
public:
	float tint = 0.0f;

	Button(float x, float y, float width, float height, Color color);

	void update(float elapsed);

	void draw();

	std::function<void()> clickCallback;
};