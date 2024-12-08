#pragma once
#include "engine.h"
#include "global.h"
#include "ui/button.h"
#include "ui/container.h"
#include "ui/sprite.h"
#include "ui/text.h"

class ModContainer : public Container
{
public:
	Text *name;
	Text *version;
	Container *buttons;
	ModContainer(std::string name, std::string version, std::string path);

	void draw();
	void updateButtons(Mod *modthing, Engine *enginething);
};

class ModsContainer : public Container
{
public:
	ModsContainer();

	void update(float elapsed);
	void draw();
};

class EngineOverview : public Container
{
public:
	Sprite *engineIcon;
	Text *engineName;
	Text *description;
	Button *playButton;
	ModsContainer *containerofmods;

	Engine *engine;

	EngineOverview(Engine *engine);

	void changeEngine(Engine *newEngine);
	void refresh() {
		changeEngine(this->engine);
	};

	void confirmEngineClose();
};