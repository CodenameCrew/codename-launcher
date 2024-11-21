#pragma once

#include "object.h"
#include "raylib.h"

class Sprite : public Object
{
public:
	Texture2D texture;
	Sprite(float x, float y, Texture2D texture);

	void draw();
};