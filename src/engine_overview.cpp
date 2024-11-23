#include "engine_overview.h"

#pragma region EngineOverview
EngineOverview::EngineOverview(Engine *engine) : Container(500, 30, 500, 600)
{
    this->engine = engine;
	engineIcon =
	    new Sprite(0, 20, LoadTexture(((std::string)(ASSETS_PATH "engine_icons/") + (std::string)(engine->iconPath)).c_str()));
    engineIcon->scale = 100 / engineIcon->width;
	engineName = new Text(50, 20, 500, 50, engine->name, 48.0f, true, WHITE, DEFAULTFONTBOLD);
	description = new Text(50, 40, 200, 40, engine->description, 18.0f, true, {255, 255, 255, 178}, DEFAULTFONT);

    playButton = new Button(400, 20, 65, 45, PRIMARYCOLOR);
    Text *playText = new Text(20, 15, 400, 400, "Open");

	add(engineIcon);
	add(engineName);
	add(description);
}

void EngineOverview::changeEngine(Engine newEngine) {
    engine = &newEngine;
    //engineIcon->texture = LoadTexture(((std::string)(ASSETS_PATH "engine_icons/") + (std::string)(engine->iconPath)).c_str());
    engineName->text = newEngine.name.c_str();
    description->text = newEngine.description.c_str();
};
#pragma endregion