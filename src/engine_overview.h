#include "ui/button.h"
#include "ui/container.h"
#include "engine.h"
#include "ui/sprite.h"
#include "ui/text.h"
#include "global.h"

class EngineOverview : public Container
{
	Sprite *engineIcon;
	Text *engineName;
	Text *description;
	Button *playButton;

	Engine *engine;

	EngineOverview(Engine *engine);

	void changeEngine(Engine *newEngine);
};