#include "engine_selector.h"

// EngineContainer
#pragma region EngineContainer
EngineContainer::EngineContainer(Engine *engine) : Button(0, 0, 400, 75, BACKGROUNDSECONDARYCOLOR)
{
	this->engine = engine;

	name = this->engine->name.c_str();
	path = this->engine->path.c_str();
	version = this->engine->version.c_str();

	spriteIcon =
	    new Sprite(15, 7, LoadTexture(((std::string)(ASSETS_PATH "engine_icons/") + (std::string)(this->engine->iconPath)).c_str()));
	spriteIcon->scale = 60.0f / spriteIcon->width;
	add(spriteIcon);
	textName = new Text(90, 17, name, 0, 0, 24.0f, false, WHITE, DEFAULTFONTBOLD);
	add(textName);
	textVersion = new Text(90, 40, version, 200, 35, 18.0f, true, {255, 255, 255, 178}, DEFAULTFONT);
	add(textVersion);

	openToLocation = new Button(300, 20, 35, 35, SECONDARYCOLOR);
	add(openToLocation);
	openToLocation->clickCallback = [&] { openFolderInExplorer(path); };
	Sprite *folderIcon = new Sprite(7.5, 7.5, LoadTexture(ASSETS_PATH "ui/folder.png"));
	openToLocation->add(folderIcon);
}
#pragma endregion

// EngineSelector
#pragma region EngineSelector
EngineSelector::EngineSelector(std::vector<Engine *> enginelist, EngineOverview *engineOverview) : Container(50, 50, 400, 600)
{
	this->engineOverview = engineOverview;

	for (Engine *engine : enginelist)
	{
		EngineContainer *enginecontainer = new EngineContainer(engine);
		enginecontainer->clickCallback = [=] { engineOverview->changeEngine(*engine); };
		add(enginecontainer);
	}

	Button *addengine = new Button(50, 660, 400, 35, PRIMARYCOLOR);
	Text *addenginetext = new Text(50, 7.5, "+ Add engine", 0, 0, 20.0f, true, WHITE, DEFAULTFONTBOLD);
	addenginetext->x = (addengine->width - addenginetext->width) / 2;
	addengine->add(addenginetext);
	addToMain(addengine);
}

void EngineSelector::update(float elapsed)
{
	float addY = 0;
	for (auto child : children)
	{
		child->y = addY;
		addY += child->height;
	}

	Container::update(elapsed);
}

void EngineSelector::draw()
{
	DrawRectangleRec(Rectangle{x, y, width, height}, LISTCOLOR);
	DrawRectangleLinesEx(Rectangle{x, y, width, height}, 2.0f, GetColor(0x00000033));

	Container::draw();
}

void EngineSelector::add(Object *child)
{
	Container::add(child);

	int iterator = 0;
	for (auto chud : children)
	{
		EngineContainer *realChud = (EngineContainer *)chud;
		if (!realChud->selected)
		{
			chud->color = (iterator % 2 == 1) ? BACKGROUNDSECONDARYCOLOR : ColorBrightness(BACKGROUNDSECONDARYCOLOR, -0.15f);
			iterator++;
		}
	}
}
#pragma endregion