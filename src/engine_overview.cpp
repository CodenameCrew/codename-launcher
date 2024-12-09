#include "engine_overview.h"
#include <algorithm>
#include <iostream>

#pragma region ModsContainer
ModsContainer::ModsContainer() : Container(0, 300, 500, 400)
{
	// nothing ig
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
ModContainer::ModContainer() : Container(0, 0, 500, 50)
{
	this->name = new Text(10, 0, "hawk tuah", 0, 0, 20.0f, false, WHITE, DEFAULTFONTBOLD);
	this->name->y = (this->height - this->name->height) / 2;
	add(this->name);
	this->version = new Text(
	    this->name->x + this->name->width + 15, this->name->y, "hawk tuah", 200, 35, 18.0f, false, {255, 255, 255, 178}, DEFAULTFONT
	);
	add(this->version);
	buttons = new Container(375, (this->height - 25) / 2, 200, 35);
	add(buttons);
}
ModContainer::ModContainer(Mod *mod) : Container(0, 0, 500, 50)
{
	this->mod = mod;
	this->name = new Text(10, 0, mod->name, 0, 0, 20.0f, false, WHITE, DEFAULTFONTBOLD);
	this->name->y = (this->height - this->name->height) / 2;
	add(this->name);
	this->version = new Text(
	    this->name->x + this->name->width + 15, this->name->y, mod->version, 200, 35, 18.0f, false, {255, 255, 255, 178}, DEFAULTFONT
	);
	add(this->version);
	buttons = new Container(375, (this->height - 25) / 2, 200, 35);
	add(buttons);
}
void ModContainer::draw()
{
	DrawRectangleRec(Rectangle{x, y, width, height}, BACKGROUNDSECONDARYCOLOR);
	DrawRectangleLinesEx(Rectangle{x, y, width, height}, 2.0f, GetColor(0x00000033));

	Container::draw();
}
void ModContainer::updateButtons(Engine *enginething)
{
	buttons->children.clear();

	float offsetX = 0.0;

	if (std::count(enginething->features.begin(), enginething->features.end(), "OPEN_WITH_MODS") > 0)
	{
		Button *openMod = new Button(offsetX, 0, 25, 25, SECONDARYCOLOR);
		buttons->add(openMod);

		Sprite *playIcon = new Sprite(0, 0, LoadTexture(ASSETS_PATH "ui/play.png"));
		playIcon->scale = 25.0 / 35.0;
		playIcon->x = (25 - (playIcon->width * playIcon->scale)) / 2;
		playIcon->y = (25 - (playIcon->height * playIcon->scale)) / 2;
		openMod->add(playIcon);

		openMod->clickCallback = [=]
		{
			std::string executablething = enginething->executeCommand;
			if (executablething.empty())
				executablething = "\"./" + enginething->rawName + "\"";
			executeProgram(enginething->path, executablething + " -mod " + mod->name, IsKeyDown(KEY_LEFT_SHIFT), nullptr);
		};

		offsetX += 35;
	}

	if (std::count(enginething->features.begin(), enginething->features.end(), "MODS_DISABLING") > 0)
	{
		Checkbox *disableMod = new Checkbox(offsetX, 0, 25, 25, SECONDARYCOLOR, LISTCOLOR);
		disableMod->isChecked = !mod->isDisabled;
		buttons->add(disableMod);

		Sprite *checkIcon = new Sprite(0, 0, LoadTexture(ASSETS_PATH "ui/check.png"));
		checkIcon->x = (25 - checkIcon->width) / 2;
		checkIcon->y = (25 - checkIcon->height) / 2;
		checkIcon->disabled = !disableMod->isChecked;
		disableMod->add(checkIcon);

		disableMod->clickCallback = [=]
		{
			mod->isDisabled = !disableMod->isChecked;
			checkIcon->disabled = !disableMod->isChecked;
			enginething->saveModAvailability();
		};
		
		offsetX += 35;
	}

	Button *openFolder = new Button(offsetX, 0, 25, 25, SECONDARYCOLOR);
	buttons->add(openFolder);
	openFolder->clickCallback = [=] { openFolderInExplorer(mod->path.c_str()); };
	offsetX += 35;

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
	version = new Text(engineName->width + 120, 30, this->engine->version, 0, 0, 28.0f, false, {255, 255, 255, 178}, DEFAULTFONT);
	description = new Text(115, 70, this->engine->description, 600 - 115, 600, 20.0f, true, {255, 255, 255, 178}, DEFAULTFONT);

	playButton = new Button(475, 20, 65, 45, PRIMARYCOLOR);
	playButton->clickCallback = [=]
	{
		std::string executablething = this->engine->executeCommand;
		if (executablething.empty())
			executablething = "\"./" + engine->rawName + "\"";
		executeProgram(this->engine->path, executablething, IsKeyDown(KEY_LEFT_SHIFT), nullptr);
		this->engine->saveModAvailability();
	};
	Text *playText = new Text(20, 15, "Open");
	playButton->add(playText);
	playText->x = (65 - playText->width) / 2;

	containerofmods = new ModsContainer();

	for (auto tempMod : this->engine->mods)
	{
		std::cout << "ADDED NEW MOD: " << tempMod->name;
		ModContainer *brandnewcontainer = new ModContainer(tempMod);
		brandnewcontainer->updateButtons(this->engine);
		containerofmods->add(brandnewcontainer);
	}

	add(engineIcon);
	add(engineName);
	add(version);
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
	version->setText(newEngine->version);
	version->x = engineName->width + 120;
	description->setText(newEngine->description.c_str());
	playButton->clickCallback = nullptr;
	playButton->clickCallback = [=]
	{
		std::string executablething = newEngine->executeCommand;
		if (executablething.empty())
			executablething = "\"./" + newEngine->rawName + "\"";
		executeProgram(newEngine->path, executablething, IsKeyDown(KEY_LEFT_SHIFT), nullptr);
		this->engine->saveModAvailability();
	};

	if (containerofmods->children.size() != engine->mods.size())
	{
		while (containerofmods->children.size() < engine->mods.size())
		{
			ModContainer *brandnewcontainer = new ModContainer();
			containerofmods->add(brandnewcontainer);
			containerofmods->update(0);
		}
		while (containerofmods->children.size() > engine->mods.size())
			containerofmods->children.pop_back();
	}

	int iter = 0;
	for (auto tempconaitner : containerofmods->children)
	{
		ModContainer *chud = (ModContainer *)tempconaitner;
		auto modthint = engine->mods[std::max(iter++, 0)];
		chud->mod = modthint;
		chud->name->setText(modthint->name);
		chud->version->setText(modthint->version);
		chud->version->x = chud->name->x + chud->name->width + 15;
		chud->updateButtons(engine);
	}
};

void EngineOverview::confirmEngineClose() {}
#pragma endregion