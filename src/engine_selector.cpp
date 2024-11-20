#include "engine_selector.h"

// EngineContainer
#pragma region EngineContainer
EngineContainer::EngineContainer(const char *engineName, Texture2D engineIcon, const char *engineVersion, const char *folderPath)
    : Container(0, 0, 400, 75)
{
	this->name = engineName;
	this->path = folderPath;
	this->version = engineVersion;

	this->spriteIcon = new Sprite(15, 7, engineIcon);
	add(this->spriteIcon);
	this->textName = new Text(90, 17, 250, 25, engineName, 24.0f, WHITE, DEFAULTFONTBOLD);
	add(this->textName);
	this->textVersion = new Text(90, 40, 250, 19, engineVersion, 18.0f, {255, 255, 255, 178}, DEFAULTFONT);
	add(this->textVersion);
}

void EngineContainer::draw()
{
	DrawRectangle(x, y, width, height, BACKGROUNDSECONDARYCOLOR);
	DrawRectangleLinesEx(Rectangle{float(x), float(y), float(width), float(height)}, 2.0f, GetColor(0x00000033));

	Container::draw();
}
#pragma endregion

// EngineSelector
#pragma region EngineSelector
EngineSelector::EngineSelector() : Container(50, 50, 400, 620)
{
	EngineContainer *codename = new EngineContainer("Codename Engine", LoadTexture(ASSETS_PATH "codename.png"), "1.0.0", "");
	add(codename);
	EngineContainer *codename2 =
	    new EngineContainer("Codename Engine Dev", LoadTexture(ASSETS_PATH "codename.png"), "dis shit ain't even releasd", "");
	add(codename2);
	EngineContainer *psych = new EngineContainer("Psych Engine", LoadTexture(ASSETS_PATH "psych.png"), "0.7.3", "");
	add(psych);
	EngineContainer *fpsplus = new EngineContainer("FPS Plus Engine", LoadTexture(ASSETS_PATH "fpsplus.png"), "6.0.1", "");
	add(fpsplus);
	EngineContainer *os =
	    new EngineContainer("OS Engine", LoadTexture(ASSETS_PATH "unknown.png"), "2 trash 2 actually have a version", "");
	add(os);
}

void EngineSelector::update(float elapsed)
{
	int addY = 0;
	for (auto child : children)
	{
		child->y = addY;
		addY += child->height;
	}

	Container::update(elapsed);
}

void EngineSelector::draw()
{
	DrawRectangle(x, y, width, height, LISTCOLOR);
	DrawRectangleLinesEx(Rectangle{float(x), float(y), float(width), float(height)}, 2.0f, GetColor(0x00000033));

	Container::draw();
}
#pragma endregion