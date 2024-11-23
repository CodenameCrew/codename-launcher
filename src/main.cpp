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

std::vector<Object *> mainchildren;
void addToMain(Object *child)
{
	mainchildren.push_back(child);
}

Vector2 mousePosition = {-100.0f, -100.0f};

void checkFileSystem()
{
	openFolderInExplorer(getDataFolder().c_str());
	if (!DirectoryExists(getDataFolder().c_str()))
	{
		MakeDirectory(getDataFolder().c_str());
		SaveFileText((getDataFolder() + "engine_data.json").c_str(), "{\n}\0");
	}
}

void parseEngines() {
	const char* rawJson = LoadFileText((getDataFolder() + "engine_data.json").c_str());
	rapidjson::Document *json;
	json->Parse(rawJson);
	for (rapidjson::Value::ConstValueIterator it = json->Begin(); it != json->End(); ++it) {
		auto string = (*it)["name"].GetString();
		TraceLog(LOG_INFO, string);
	}
}

int main()
{
	checkFileSystem();
	parseEngines();

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
	InitWindow(1280, 720, "Hello Raylib");

	std::vector<Engine *> enginers = {};
	enginers.push_back(new Engine("Codename engine", ".", "1.0.0", "codename.png"));
	enginers.push_back(new Engine("CNE Dev", ".", "dev.0.0", "codename.png"));
	enginers.push_back(new Engine("Psych engine", ".", "0.7.3", "psych.png"));
	enginers.push_back(new Engine("Psych engine", ".", "github branch: dev", "psych.png"));
	enginers.push_back(new Engine("FPS Plus engine", ".", "6.0.1", "fpsplus.png"));
	enginers.push_back(new Engine("OS engine", ".", "trash trash trash trash trash trash trash trash trash trash ", "unknown.png"));

	EngineOverview *there = new EngineOverview(enginers.front());
	addToMain(there);

	EngineSelector *here = new EngineSelector(enginers, there);
	addToMain(here);

	while (!WindowShouldClose())
	{
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