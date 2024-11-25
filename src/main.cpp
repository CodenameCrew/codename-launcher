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

void parseEngines()
{
	const char *rawJson = LoadFileText((getDataFolder() + "engine_data.json").c_str());
	std::vector<Engine> engines;

	rapidjson::Document document;
	document.Parse(rawJson);

	if (document.IsArray())
	{
		for (const auto &engineJson : document.GetArray())
		{
			Engine engine = Engine();

			engine.name = engineJson["name"].GetString();
			engine.version = engineJson["version"].GetString();
			engine.description = engineJson["description"].GetString();
			engine.path = engineJson["path"].GetString();
			engine.modsPath = engineJson["modsPath"].GetString();
			engine.addonsPath = engineJson["addonsPath"].GetString();
			engine.executeCommand = engineJson["executeCommand"].GetString();

			const auto &statsJson = engineJson["stats"];
			engine.stats.storage = statsJson["storage"].GetString();
			engine.stats.modsStorage = statsJson["modsStorage"].GetString();
			engine.stats.lastUpdated = statsJson["lastUpdated"].GetString();

			const auto &modsJson = engineJson["mods"];
			for (const auto &modJson : modsJson.GetArray())
			{
				Mod mod;
				mod.name = modJson["name"].GetString();
				mod.storage = modJson["storage"].GetString();
				engine.mods.push_back(mod);
			}

			const auto &features = engineJson["features"];
			for (const auto &feature : features.GetArray())
			{
				engine.features.push_back(feature.GetString());
			}

			engines.push_back(engine);
		}
	}

	for (const auto &engine : engines)
	{
		std::cout << "Engine Name: " << engine.name << "\n";
		std::cout << "Version: " << engine.version << "\n";
		std::cout << "Description: " << engine.description << "\n";
		std::cout << "Storage: " << engine.stats.storage << "\n";
		std::cout << "Features: ";
		for (const auto &feature : engine.features)
		{
			std::cout << feature << " ";
		}
		std::cout << "\n\n";
	}
}

int main()
{
	checkFileSystem();
	parseEngines();

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
	InitWindow(1280, 720, "Hello Raylib");

	std::vector<Engine *> enginers = {};
	enginers.push_back(new Engine(
	    "Codename engine",
	    "this engine is awful",
	    "CodenameEngine",
	    getPath("CodenameEngine"),
	    "codename.png",
	    "1.0.0",
	    CODENAME,
	    getPath("CodenameEngine/mods"),
	    getPath("CodenameEngine/addons"),
	    "./CodenameEngine --m pj-party"
	));
	enginers.push_back(new Engine(
	    "CNE Dev",
	    "this engine is awful for developers",
	    "CodenameEngine",
	    getPath("build-for-devs 2"),
	    "codename.png",
	    "dev",
	    CODENAME,
	    getPath("build-for-devs 2/mods"),
	    getPath("build-for-devs 2/addons")
	));
	enginers.push_back(new Engine(
	    "Psych engine",
	    "this engine is actually good",
	    "PsychEngine.exe",
	    getPath("PsychEngine"),
	    "psych.png",
	    "1.0.3",
	    PSYCH,
	    getPath("PsychEngine/mods"),
	    getPath("PsychEngine/addons"),
	    "wine ./PsychEngine.exe"
	));
	enginers.push_back(new Engine(
	    "FPS Plus engine",
	    "i lowkey hate this mfing engine actually",
	    "FunkinFPSPlus.exe",
	    getPath("FPS Plus"),
	    "fpsplus.png",
	    "6.0.idk anymore",
	    FPSPLUS,
	    getPath("FPS Plus/mods"),
	    getPath("FPS Plus/addons"),
	    "wine ./FunkinFPSPlus.exe"
	));

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