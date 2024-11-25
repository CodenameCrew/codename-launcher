#pragma once

#include "object.h"
#include "raylib.h"
#include "raymath.h"

class Container : public Object
{
public:
	float scroll = 0;
	float scrollMax = 0;
	Container(float x, float y, float width, float height);

	virtual void update(float elapsed);

	virtual void draw();
};