#include "sprite.h"

Sprite::Sprite(float x, float y, Texture2D texture) : Object(x, y, 0, 0)
{
	this->texture = texture;
	this->width = texture.width;
	this->height = texture.height;
	SetTextureFilter(this->texture, TEXTURE_FILTER_BILINEAR);
};

void Sprite::draw()
{
	DrawTextureEx(texture, Vector2{x, y}, angle, scale, color);

	Object::draw();
}