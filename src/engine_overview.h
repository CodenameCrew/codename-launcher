#pragma once
#include "engine.h"
#include "global.h"
#include "ui/button.h"
#include "ui/checkbox.h"
#include "ui/container.h"
#include "ui/sprite.h"
#include "ui/text.h"

class ModContainer : public Container
{
public:
	Mod *mod;
	Text *name;
	Text *version;
	Container *buttons;

	ModContainer();
	ModContainer(Mod *mod);

	void draw();
	void updateButtons(Engine *enginething);
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
	Text *version;
	Text *description;
	Button *playButton;
	ModsContainer *containerofmods;

	Engine *engine;

	EngineOverview(Engine *engine);

	void changeEngine(Engine *newEngine);
	void refresh()
	{
		changeEngine(this->engine);
	};

	void confirmEngineClose();
};