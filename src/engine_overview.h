#include "engine.h"
#include "global.h"
#include "ui/button.h"
#include "ui/container.h"
#include "ui/sprite.h"
#include "ui/text.h"

class EngineOverview : public Container
{
public:
	Sprite *engineIcon;
	Text *engineName;
	Text *description;
	Button *playButton;

	Engine *engine;

	EngineOverview(Engine *engine);

	void changeEngine(Engine newEngine);
};