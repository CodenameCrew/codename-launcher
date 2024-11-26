#include "engine_overview.h"

#pragma region ModsContainer
void ModsContainer::draw()
{
	DrawRectangleRec(Rectangle{x, y, width, height}, LISTCOLOR);
	DrawRectangleLinesEx(Rectangle{x, y, width, height}, 2.0f, GetColor(0x00000033));

	Container::draw();
}
#pragma endregion

#pragma region EngineOverview
EngineOverview::EngineOverview(Engine *engine) : Container(500, 30, 600, 600)
{
	this->engine = engine;
	engineIcon = new Sprite(0, 0, LoadTexture(engine->iconPath.c_str()));
	TraceLog(LOG_INFO, engine->iconPath.c_str());
	engineIcon->scale = 100 / engineIcon->width;
	engineName = new Text(110, 20, this->engine->name, 0, 0, 48.0f, true, WHITE, DEFAULTFONTBOLD);
	description = new Text(115, 70, this->engine->description, 600-115, 600, 20.0f, true, {255, 255, 255, 178}, DEFAULTFONT);

	playButton = new Button(475, 20, 65, 45, PRIMARYCOLOR);
	playButton->clickCallback = [=]
	{
		std::string executablething = this->engine->executeCommand;
		if (executablething.empty())
			executablething = "\"./" + engine->rawName + "\"";
				executeProgram(this->engine->path, executablething, false, nullptr);
	};
	Text *playText = new Text(20, 15, "Open");
	playButton->add(playText);
	playText->x = (65 - playText->width) / 2;

	int it = 0;
	for (auto mod : this->engine->mods)
	{
		TraceLog(LOG_INFO, mod.name.c_str());
		Text *showMod = new Text(0, 400 + (50 * it++), mod.name);
		add(showMod);
	}

	add(engineIcon);
	add(engineName);
	add(description);
	add(playButton);
}

void EngineOverview::changeEngine(Engine newEngine)
{
	engine = &newEngine;
	UnloadTexture(engineIcon->texture);
	engineIcon->texture = LoadTexture(engine->iconPath.c_str());
	engineName->setText(newEngine.name.c_str());
	description->setText(newEngine.description.c_str());
	playButton->clickCallback = nullptr;
	playButton->clickCallback = [=]
	{
		std::string executablething = newEngine.executeCommand;
		if (executablething.empty())
			executablething = "\"./" + newEngine.rawName + "\"";
		executeProgram(newEngine.path, executablething, false, nullptr);
	};
};

void EngineOverview::confirmEngineClose() {
	
}
#pragma endregion