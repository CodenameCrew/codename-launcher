#include "sprite.h"

Sprite::Sprite(float x, float y, Texture2D texture) : Object(x, y, 0, 0)
{
	this->texture = texture;
	this->width = texture.width;
	this->height = texture.height;
	GenTextureMipmaps(&this->texture);
	SetTextureFilter(this->texture, TEXTURE_FILTER_TRILINEAR);
	SetTextureWrap(this->texture, TEXTURE_WRAP_CLAMP);
};

void Sprite::draw()
{
	DrawTextureEx(texture, Vector2{x, y}, angle, scale, color);

	Object::draw();
}