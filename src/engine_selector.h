#include "raylib.h"
#include "ui/container.h"
#include "ui/sprite.h"
#include "ui/text.h"

class EngineContainer : public Container
{
public:
	const char *name;
	const char *path;
	const char *version;

	Sprite *spriteIcon;
	Text *textName;
	Text *textVersion;

	EngineContainer(const char *engineName, Texture2D engineIcon, const char *engineVersion, const char *folderPath);

	void draw();
};

class EngineSelector : public Container
{
public:
	EngineSelector();

	void update(float elapsed);

	void draw();
};