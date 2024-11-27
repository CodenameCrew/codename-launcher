/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you
--  wrote the original software. If you use this software in a product, an acknowledgment
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "main.h"
#include <iostream>

std::vector<Object *> mainchildren;
void addToMain(Object *child)
{
	mainchildren.push_back(child);
}

Vector2 mousePosition = {-100.0f, -100.0f};

void checkFileSystem()
{
	if (!DirectoryExists(getDataFolder().c_str()))
	{
		MakeDirectory(getDataFolder().c_str());
		SaveFileText(getPath("engine_data.json").c_str(), "{\n}\0");
	}
}

std::vector<Engine *> engines;
EngineSelector *leftPanel;
EngineOverview *rightPanel;

int engineJsonLastSize = 0;

int parseEngines()
{
	bool firstTime = false;
	char *rawJson = LoadFileText((getDataFolder() + "engine_data.json").c_str());
	int jsonSize = GetFileLength((getDataFolder() + "engine_data.json").c_str());
	if (engineJsonLastSize == 0) firstTime = true;
	TraceLog(LOG_INFO, BOOL_STR(engineJsonLastSize == jsonSize));
	if (engineJsonLastSize == jsonSize && !firstTime) return 0;
	engineJsonLastSize = jsonSize;

	rapidjson::Document document;
	document.Parse(rawJson);

	UnloadFileText(rawJson);

	if (document.IsArray())
	{
		auto legitArray = document.GetArray();
		if (firstTime) {
			for (int i = 0; i < legitArray.Size(); i++)
				engines.push_back(new Engine());
		}
		for (int i = 0; i < legitArray.Size(); i++)
		{
			Engine *engine = engines[i];
			const auto &engineJson = legitArray[i];

			engine->name = engineJson["name"].GetString();
			engine->version = engineJson["version"].GetString();
			engine->description = engineJson["description"].GetString();
			engine->path = getPath(engineJson["path"].GetString());
			engine->iconPath = engine->path + "/engine_icon.png";
			engine->modsPath = getPath(engineJson["modsPath"].GetString());
			engine->addonsPath = getPath(engineJson["addonsPath"].GetString());
			engine->executeCommand = engineJson["executeCommand"].GetString();

			const auto &statsJson = engineJson["stats"];
			engine->stats.lastUpdated = statsJson["lastUpdated"].GetString();

			const auto &features = engineJson["features"];
			if (!engine->features.empty()) engine->features.clear();
			for (const auto &feature : features.GetArray())
			{
				engine->features.push_back(feature.GetString());
			}
		}
	}

	for (const auto &engine : engines)
	{
		std::cout << "Engine Name: " << engine->name << "\n";
		std::cout << "Version: " << engine->version << "\n";
		std::cout << "Description: " << engine->description << "\n";
		std::cout << "Storage: " << engine->stats.storage << "\n";
		std::cout << "Features: ";
		for (const auto &feature : engine->features)
		{
			std::cout << feature << " ";
		}
		std::cout << "\n\n";
	}
	return 1;
}

void checkForChanges() {
	if (parseEngines() == 1) {
		leftPanel->refresh(engines);
		rightPanel->refresh();
	}
}

bool wasFocused = false;

int main()
{
	checkFileSystem();
	parseEngines();

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
	InitWindow(1280, 720, "Hello Raylib");

	rightPanel = new EngineOverview(engines.front());
	addToMain(rightPanel);

	leftPanel = new EngineSelector(engines, rightPanel);
	addToMain(leftPanel);

	while (!WindowShouldClose())
	{
		bool isFocused = IsWindowFocused();
		if (isFocused && !wasFocused)
		{
			checkForChanges();
		}

		wasFocused = isFocused;

		mousePosition = GetMousePosition();
		curCursorState = 1;
		for (auto child : mainchildren)
		{
			child->update(GetFrameTime());
		}
		SetMouseCursor(curCursorState);

		BeginDrawing();
		ClearBackground(BACKGROUNDPRIMARYCOLOR);

		// draw some text using the default font
		DrawText("Hello Raylib", 200, 200, 20, GetColor(0xff0000ff));

		for (auto child : mainchildren)
		{
			child->draw();
		}

		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}