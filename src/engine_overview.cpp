#include "engine_overview.h"
#include <iostream>
#include <algorithm>

#pragma region ModsContainer
ModsContainer::ModsContainer() : Container(0, 300, 500, 400) {
	//nothing ig
}

void ModsContainer::draw()
{
	DrawRectangleRec(Rectangle{x, y, width, height}, LISTCOLOR);
	DrawRectangleLinesEx(Rectangle{x, y, width, height}, 2.0f, GetColor(0x00000033));

	Container::draw();
}

void ModsContainer::update(float elapsed)
{

	float addY = 0;
	for (auto child : children)
	{
		child->y = addY;
		addY += child->height;
	}
	
	Container::update(elapsed);
}
#pragma endregion

#pragma region ModContainer
ModContainer::ModContainer(std::string name, std::string version, std::string path) : Container(0, 0, 500, 50) {
	this->name = new Text(10, 0, name, 0, 0, 20.0f, false, WHITE, DEFAULTFONTBOLD);
	this->name->y = (this->height - this->name->height) / 2;
	add(this->name);
	this->version = new Text(this->name->x + this->name->width + 15, this->name->y, version, 200, 35, 18.0f, false, {255, 255, 255, 178}, DEFAULTFONT);
	add(this->version);
	buttons = new Container(200, (this->height - 35) / 2, 200, 35);
	add(buttons);
}
void ModContainer::draw()
{
	DrawRectangleRec(Rectangle{x, y, width, height}, BACKGROUNDSECONDARYCOLOR);
	DrawRectangleLinesEx(Rectangle{x, y, width, height}, 2.0f, GetColor(0x00000033));

	Container::draw();
}
void ModContainer::updateButtons(Mod *modthing, Engine *enginething) {
	buttons->children.clear();

	float offsetX = 0.0;

	if (std::count(enginething->features.begin(), enginething->features.end(), "OPEN_WITH_MODS") > 0) {
		Button *openMod = new Button(offsetX, 0, 35, 35, SECONDARYCOLOR);
		buttons->add(openMod);
	}

	Button *openFolder = new Button(this->width - 100, (this->height - 25) / 2, 25, 25, SECONDARYCOLOR);
	buttons->add(openFolder);
	openFolder->clickCallback = [=] { openFolderInExplorer(getPath(modthing->path).c_str()); };
	Sprite *folderIcon = new Sprite(0, 0, LoadTexture(ASSETS_PATH "ui/folder.png"));
	folderIcon->scale = 25.0 / 35.0;
	folderIcon->x = (25 - (folderIcon->width * folderIcon->scale)) / 2;
	folderIcon->y = (25 - (folderIcon->height * folderIcon->scale)) / 2;
	openFolder->add(folderIcon);
}
#pragma endregion

#pragma region EngineOverview
EngineOverview::EngineOverview(Engine *engine) : Container(500, 30, 600, 600)
{
	this->engine = engine;
	engineIcon = new Sprite(0, 0, LoadTexture(engine->iconPath.c_str()));
	TraceLog(LOG_INFO, engine->iconPath.c_str());
	engineIcon->scale = 100 / engineIcon->width;
	engineName = new Text(110, 20, this->engine->name, 0, 0, 48.0f, true, WHITE, DEFAULTFONTBOLD);
	description = new Text(115, 70, this->engine->description, 600 - 115, 600, 20.0f, true, {255, 255, 255, 178}, DEFAULTFONT);

	playButton = new Button(475, 20, 65, 45, PRIMARYCOLOR);
	playButton->clickCallback = [=]
	{
		std::string executablething = this->engine->executeCommand;
		if (executablething.empty())
			executablething = "\"./" + engine->rawName + "\"";
		executeProgram(this->engine->path, executablething, IsKeyDown(KEY_LEFT_SHIFT), nullptr);
	};
	Text *playText = new Text(20, 15, "Open");
	playButton->add(playText);
	playText->x = (65 - playText->width) / 2;

	containerofmods = new ModsContainer();

	for (auto tempMod : this->engine->mods) {
		std::cout << "ADDED NEW MOD: " << tempMod->name;
		ModContainer *brandnewcontainer = new ModContainer(tempMod->name, tempMod->version, tempMod->path);
		containerofmods->add(brandnewcontainer);
	}

	add(engineIcon);
	add(engineName);
	add(description);
	add(playButton);

	add(containerofmods);
}

void EngineOverview::changeEngine(Engine *newEngine)
{
	engine = newEngine;
	UnloadTexture(engineIcon->texture);
	engineIcon->texture = LoadTexture(engine->iconPath.c_str());
	engineName->setText(newEngine->name.c_str());
	description->setText(newEngine->description.c_str());
	playButton->clickCallback = nullptr;
	playButton->clickCallback = [=]
	{
		std::string executablething = newEngine->executeCommand;
		if (executablething.empty())
			executablething = "\"./" + newEngine->rawName + "\"";
		executeProgram(newEngine->path, executablething, IsKeyDown(KEY_LEFT_SHIFT), nullptr);
	};

	if (containerofmods->children.size() != engine->mods.size()) {
		while (containerofmods->children.size() < engine->mods.size()) {
			ModContainer *brandnewcontainer = new ModContainer("hawk tuah", "hawk tuah", "hawk tuah");
			containerofmods->add(brandnewcontainer);
		}
		while (containerofmods->children.size() > engine->mods.size()) containerofmods->children.pop_back();
	}

	int iter = 0;
	for (auto tempconaitner : containerofmods->children) {
		ModContainer *chud = (ModContainer *)tempconaitner;
		auto modthint = engine->mods[std::max(iter++, 0)];
		chud->name->setText(modthint->name);
		chud->version->setText(modthint->version);
		chud->version->x = chud->name->x + chud->name->width + 15;
		chud->openFolder->clickCallback = [=] {
 			openFolderInExplorer(getPath(modthint->path).c_str());
		};
	}
};

void EngineOverview::confirmEngineClose() {}
#pragma endregion