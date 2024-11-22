#include "engine_overview.h"

EngineOverview::EngineOverview(Engine *engine) : Container(500, 30, 500, 600) {
    engineIcon = new Sprite(20, 20, LoadTexture(engine->iconPath));
    engineName = new Text(50, 20, 500, 50, engine->name, 30.0f, true, WHITE, DEFAULTFONTBOLD);
    description = new Text(50, 40, 200, 40, engine->description, 18.0f, true, {255, 255, 255, 178}, DEFAULTFONT);
    
}