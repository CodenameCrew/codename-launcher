#include "engine_overview.h"
#include <iostream>

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
	Text *nametext = new Text(10, 10, name);
	add(nametext);
}
void ModContainer::draw()
{
	DrawRectangleRec(Rectangle{x, y, width, height}, BACKGROUNDSECONDARYCOLOR);
	DrawRectangleLinesEx(Rectangle{x, y, width, height}, 2.0f, GetColor(0x00000033));

	Container::draw();
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
};

void EngineOverview::confirmEngineClose() {}
#pragma endregion