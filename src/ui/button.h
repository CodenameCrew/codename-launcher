#pragma once

#include "object.h"
#include "raylib.h"
#include "raymath.h"
#include <functional>

class Button : public Object
{
public:
	std::function<void()> clickCallback = nullptr;

	float tint = 0.0f;

	Button(int x, int y, int width, int height, Color color);

	void update(float elapsed);

	void draw();
};