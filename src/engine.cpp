#include "engine.h"
#include "global.h"

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

	if (!this->modsPath.empty())
	{
		FilePathList modSearch = LoadDirectoryFiles(this->modsPath.c_str());
		for (auto i = 0; i < (int)modSearch.count; i++)
		{
			auto curpath = modSearch.paths[i];
			if (DirectoryExists(curpath))
			{
				this->mods.push_back(
				    new Mod(GetFileName(curpath), "idk bro", "reeks of humeros juice", curpath, MOD, this->type)
				);
			}
		}
	}
}