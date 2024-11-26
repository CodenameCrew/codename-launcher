#pragma once

#include "main.h"
#include "engine.h"
#include "raylib.h"
#include "ui/button.h"
#include "ui/container.h"
#include "ui/sprite.h"
#include "ui/text.h"

class EngineContainer : public Button
{
public:
	Engine *engine;

	const char *name;
	const char *path;
	const char *version;

	Sprite *spriteIcon;
	Text *textName;
	Text *textVersion;
	Button *openToLocation;

	bool selected = false;

	EngineContainer(Engine *engine);
};
class EngineSelector : public Container
{
public:
	Button *addbutton;
	EngineOverview *engineOverview;

	EngineSelector(std::vector<Engine *> enginelist, EngineOverview *engineOverview);

	void update(float elapsed);

	void draw();

	void add(Object *child);
};