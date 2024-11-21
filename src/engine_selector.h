#pragma once

#include "raylib.h"
#include "ui/container.h"
#include "ui/button.h"
#include "ui/sprite.h"
#include "ui/text.h"
#include "main.h"

class Engine {
	public:
	const char *name;

	const char *path;
	const char *modsPath;
	const char *addonsPath;
	const char *iconPath;

	const char *version;

	Engine(const char* name, const char* path, const char* version, const char* iconPath);

	void approximateEngine();

	void detectModsFolder();

	void detectAddonsFolder();
};

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

	EngineSelector(std::vector<Engine*> enginelist);

	void update(float elapsed);

	void draw();
	
	void add(Object* child);
};