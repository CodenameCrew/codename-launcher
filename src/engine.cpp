#include "engine.h"
#include "global.h"
#include <algorithm>
#include <iostream>

Mod::Mod() {}
Mod::Mod(std::string name, std::string version, std::string description, std::string path, ModType type, EngineType supportType)
{
	this->name = name;
	this->version = version;
	this->description = description;
	this->path = path;
	this->type = type;
	this->supportType = supportType;
}

Engine::Engine() {}

Engine::Engine(
    std::string name,
    std::string description,
    std::string rawName,
    std::string path,
    std::string iconPath,
    std::string version,
    EngineType type,
    std::string modsPath,
    std::string addonsPath,
    std::string executeCommand
)
{
	this->name = name;
	this->description = description;
	this->rawName = rawName;
	this->path = path;
	this->modsPath = modsPath;
	this->addonsPath = addonsPath;
	this->iconPath = iconPath;
	this->version = version;
	this->type = type;
	this->executeCommand = executeCommand;

	loadData();
};

void Engine::loadData()
{

	if (rawName.empty())
		this->rawName = findExecutable(path);
	TraceLog(LOG_INFO, this->rawName.c_str());

	approximateEngineType();

	if (!this->modsPath.empty())
	{
		FilePathList modSearch = LoadDirectoryFiles(this->modsPath.c_str());
		if ((int)modSearch.count != mods.size())
			while ((int)modSearch.count > mods.size())
				mods.push_back(new Mod());
		int iterator = 0;
		for (auto i = 0; i < (int)modSearch.count; i++)
		{
			auto curpath = modSearch.paths[i];
			if (DirectoryExists(curpath))
			{
				TraceLog(LOG_INFO, curpath);
				Mod *brandnewmod = mods[iterator++];
				brandnewmod->name = GetFileName(curpath);
				brandnewmod->version = "v24432";
				brandnewmod->description = "reeks of humerus juice";
				brandnewmod->path = curpath;
			}
		}
		if (mods.size() > iterator)
			while (mods.size() > iterator)
				mods.pop_back();
		UnloadDirectoryFiles(modSearch);
	}

	if (type == PSYCH && FileExists((path + "modsList.txt").c_str()))
	{
		char *modList = LoadFileText((path + "modsList.txt").c_str());
		for (auto mod : split(modList, "\n"))
		{
			if (std::count(mod.begin(), mod.end(), '|') == 0) continue;
			auto modStatus = split(mod, "|");

			auto lambdafunction = [=](const Mod *m) -> bool { return m->name == modStatus[0]; };
			Mod *selectMod = nullptr;
			auto it = std::find_if(mods.begin(), mods.end(), lambdafunction);
			if (it != mods.end())
			{
				selectMod = *it;
			}
			selectMod->isDisabled = modStatus[1] == "0";
		}
		UnloadFileText(modList);
	}
	if (type == FPSPLUS && FileExists((modsPath + "disabled").c_str()) && GetFileLength((modsPath + "disabled").c_str()) != 0)
	{
		char *modList = LoadFileText((modsPath + "disabled").c_str());
		for (auto mod : split(modList, "\n"))
		{
			auto lambdafunction = [=](const Mod *m) -> bool { return m->name == mod; };
			Mod *selectMod = nullptr;
			auto it = std::find_if(mods.begin(), mods.end(), lambdafunction);
			if (it != mods.end())
			{
				selectMod = *it;
			}
			if (selectMod == nullptr)
				continue;
			selectMod->isDisabled = true;
		}
		UnloadFileText(modList);
	}
}

void Engine::approximateEngineType()
{
	std::vector<EngineType> engineTypes = {};

	FilePathList engineFiles = LoadDirectoryFilesEx(this->path.c_str(), NULL, true);
	for (auto i = 0; i < (int)engineFiles.count; i++)
	{
		auto curpath = engineFiles.paths[i];

		if (std::string(curpath).rfind("mods/") != std::string::npos || std::string(curpath).rfind("addons/") != std::string::npos)
			continue;

		if (std::string(GetFileName(curpath)).rfind("ShadowBump", 0) == 0 ||
		    std::string(GetFileName(curpath)).rfind("cry_about_it", 0) == 0 ||
		    std::string(GetFileName(curpath)).rfind("chart_quant", 0) == 0)
		{
			engineTypes.push_back(PSYCH);
			TraceLog(LOG_INFO, "dis one seems to be psych yep");
		}

		if (std::string(GetFileName(curpath)).rfind("editorBlurFast", 0) == 0 ||
		    std::string(GetFileName(curpath)).rfind("audio-volume-full", 0) == 0 ||
		    std::string(GetFileName(curpath)).rfind("strumline-info-bg", 0) == 0)
		{
			engineTypes.push_back(CODENAME);
			TraceLog(LOG_INFO, "dis one seems to be codename yep");
		}
	}
	UnloadDirectoryFiles(engineFiles);
	if (rawName.rfind("PsychEngine", 0) == 0)
	{
		engineTypes.push_back(PSYCH);
		TraceLog(LOG_INFO, "dis one seems to be psych yep");
	}
	if (rawName.rfind("CodenameEngine", 0) == 0)
	{
		engineTypes.push_back(CODENAME);
		TraceLog(LOG_INFO, "dis one seems to be codename yep");
	}
	if (rawName.rfind("FunkinFPSPlus", 0) == 0)
	{
		engineTypes.push_back(FPSPLUS);
		TraceLog(LOG_INFO, "dis one seems to be fpsplus yep");
	}

	if (engineTypes.size() == 0)
	{
		type = UNKNOWN;
		TraceLog(LOG_INFO, "ur engine is incredibly fukin mysterious");
		return;
	}

	if (engineTypes.size() > 1 && std::count(engineTypes.begin(), engineTypes.end(), engineTypes[0]) != engineTypes.size())
	{
		type = UNKNOWN;
		TraceLog(LOG_INFO, "is ur fukin engine an amalgamation or smth???");
	}
	else
		type = engineTypes[0];
}

void Engine::saveModAvailability()
{
	std::string fileText = "";
	char *parsedFileText;
	switch (type)
	{
	case CODENAME | OTHER | UNKNOWN:
		//do nothing
		break;
	case PSYCH:
		TraceLog(LOG_INFO, "saving for pshych mengnes");

		for (auto mod : mods)
		{
			fileText += mod->name + "|" + (mod->isDisabled ? "0" : "1") + "\n";
		}

		parsedFileText = new char[fileText.size() + 1];
		std::copy(fileText.begin(), fileText.end(), parsedFileText);
		parsedFileText[fileText.size()] = '\0';
		SaveFileText((path + "modsList.txt").c_str(), parsedFileText);
		break;
	case FPSPLUS:

		for (auto mod : mods)
		{
			if (mod->isDisabled)
				fileText += mod->name + "\n";
		}

		parsedFileText = new char[fileText.size() + 1];
		std::copy(fileText.begin(), fileText.end(), parsedFileText);
		parsedFileText[fileText.size()] = '\0';
		SaveFileText((modsPath + "disabled").c_str(), parsedFileText);
		break;
	case VSLICE:
		// todo
		break;
	}
}