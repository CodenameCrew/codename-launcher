#include "sprite.h"

Sprite::Sprite(float x, float y, Texture2D texture) : Object(x, y, 0, 0)
{
	this->texture = texture;
	this->width = texture.width;
	this->height = texture.height;
};

void Sprite::draw()
{
	DrawTextureV(texture, Vector2{x, y}, color);

	Object::draw();
}