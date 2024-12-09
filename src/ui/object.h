#pragma once

#include "global.h"
#include "raylib.h"
#include "raymath.h"
#include <vector>

class Object
{
public:
	float x = 0;
	float y = 0;
	float width = 0;
	float height = 0;
	bool disabled = false;
	Object *parent = nullptr;

	Color color = {255, 255, 255, 255};

	std::vector<Object *> children;

	bool isHovering = false;
	bool hoverable = false;

	Object(float x, float y, float width, float height);
	virtual ~Object() = default;

	virtual void add(Object *child);
	virtual void remove(Object *child);

	virtual void update(float elapsed);
	virtual void draw();
};