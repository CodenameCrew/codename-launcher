#include "raylib.h"
#include "ui/container.h"
#include "ui/button.h"
#include "ui/sprite.h"
#include "ui/text.h"

class EngineContainer : public Button
{
public:
	const char *name;
	const char *path;
	const char *version;

	Sprite *spriteIcon;
	Text *textName;
	Text *textVersion;
	Button *openToLocation;

	bool selected = false;

	EngineContainer(const char *engineName, Texture2D engineIcon, const char *engineVersion, const char *folderPath);
};

class EngineSelector : public Container
{
public:
	EngineSelector();

	void update(float elapsed);

	void draw();
	
	void add(Object* child);
};