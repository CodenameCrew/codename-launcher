#include "sprite.h"

Sprite::Sprite(int x, int y, Texture2D texture) : Object(x, y, 0, 0)
{
	this->texture = texture;
	this->width = texture.width;
	this->height = texture.height;
};

void Sprite::draw()
{
	DrawTexture(texture, x, y, color);

	Object::draw();
}