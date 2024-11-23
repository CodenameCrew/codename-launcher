#include "engine_overview.h"

#pragma region EngineOverview
EngineOverview::EngineOverview(Engine *engine) : Container(500, 30, 500, 600)
{
    this->engine = engine;
	engineIcon =
	    new Sprite(0, 0, LoadTexture(((std::string)(ASSETS_PATH "engine_icons/") + (std::string)(engine->iconPath)).c_str()));
    engineIcon->scale = 100 / engineIcon->width;
	engineName = new Text(110, 20, engine->name, 0, 0, 48.0f, true, WHITE, DEFAULTFONTBOLD);
	description = new Text(50, 40, engine->description, 0, 0, 18.0f, true, {255, 255, 255, 178}, DEFAULTFONT);

    playButton = new Button(400, 20, 65, 45, PRIMARYCOLOR);
    Text *playText = new Text(20, 15, "Open");
    playButton->add(playText);

	add(engineIcon);
	add(engineName);
	add(description);
}

void EngineOverview::changeEngine(Engine newEngine) {
    engine = &newEngine;
    UnloadTexture(engineIcon->texture);
    engineIcon->texture = LoadTexture(((std::string)(ASSETS_PATH "engine_icons/") + (std::string)(engine->iconPath)).c_str());
    engineName->setText(newEngine.name.c_str());
    description->setText(newEngine.description.c_str());
};
#pragma endregion