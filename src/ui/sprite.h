#pragma once

#include "object.h"
#include "raylib.h"

class Sprite : public Object
{
private:
public:
	Texture2D texture;
	float scale = 1;
	float angle = 0;
	Sprite(float x, float y, Texture2D texture);

	void draw();
};