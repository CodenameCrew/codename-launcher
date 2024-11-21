#include "engine_selector.h"

// EngineContainer
#pragma region EngineContainer
EngineContainer::EngineContainer(const char *engineName, Texture2D engineIcon, const char *engineVersion, const char *folderPath)
    : Button(0, 0, 400, 75, BACKGROUNDSECONDARYCOLOR)
{
	this->name = engineName;
	this->path = folderPath;
	this->version = engineVersion;

	this->spriteIcon = new Sprite(15, 7, engineIcon);
	add(this->spriteIcon);
	this->textName = new Text(90, 17, 200, 25, engineName, 24.0f, false, WHITE, DEFAULTFONTBOLD);
	add(this->textName);
	this->textVersion = new Text(90, 40, 200, 40, engineVersion, 18.0f, true, {255, 255, 255, 178}, DEFAULTFONT);
	add(this->textVersion);

    this->openToLocation = new Button(300, 20, 35, 35, SECONDARYCOLOR);
    add(this->openToLocation);
    openToLocation->clickCallback = [&] {
        openFolderInExplorer("here");
    };
    Sprite* folderIcon = new Sprite(7.5, 7.5, LoadTexture(ASSETS_PATH "ui/folder.png"));
    this->openToLocation->add(folderIcon);
}
#pragma endregion

// EngineSelector
#pragma region EngineSelector
EngineSelector::EngineSelector() : Container(50, 50, 400, 620)
{
	EngineContainer *codename = new EngineContainer("Codename Engine", LoadTexture(ASSETS_PATH "engine_icons/codename.png"), "1.0.0", "");
	add(codename);
	EngineContainer *codename2 =
	    new EngineContainer("CNE Dev", LoadTexture(ASSETS_PATH "engine_icons/codename.png"), "dis shit ain't even releasd", "");
	add(codename2);
	EngineContainer *psych = new EngineContainer("Psych Engine", LoadTexture(ASSETS_PATH "engine_icons/psych.png"), "0.7.3", "");
	add(psych);
	EngineContainer *fpsplus = new EngineContainer("FPS Plus Engine", LoadTexture(ASSETS_PATH "engine_icons/fpsplus.png"), "6.0.1", "");
	add(fpsplus);
	EngineContainer *os =
	    new EngineContainer("OS Engine", LoadTexture(ASSETS_PATH "engine_icons/unknown.png"), "2 trash 2 actually have a version", "");
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
	DrawRectangleLinesEx(Rectangle{x, y, width, height}, 2.0f, GetColor(0x00000033));

	Container::draw();
}

void EngineSelector::add(Object* child) {
    Container::add(child);

    int iterator = 0;
    for (auto chud : children) {
        EngineContainer* realChud = (EngineContainer*)chud;
        if (!realChud->selected) {
            chud->color = (iterator % 2 == 1) ? BACKGROUNDSECONDARYCOLOR : ColorBrightness(BACKGROUNDSECONDARYCOLOR, -0.15f);
            iterator++;
        }
    }
}
#pragma endregion