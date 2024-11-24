#pragma once
#include "global.h"
#include <vector>
#include <string>

enum ModType
{
	MOD,
	ADDON
};

enum EngineType {
	PSYCH,
	CODENAME,
	VSLICE,
	FPSPLUS,
	OTHER,
	UNKNOWN
};

class Mod
{
	std::string name;
	std::string rawName;
	std::string version;
	std::string description;

	std::string path;

	ModType type = MOD;
	EngineType supportType;

	void approximateModType();

	std::string pageLink;
};

class Engine
{
public:
	std::string name;
	std::string description;

	std::string rawName;
	std::string path;
	std::string modsPath;
	std::string addonsPath;
	std::string iconPath;

	std::string version;

	EngineType type;

	const std::vector<Mod> mods = {};

	Engine(std::string name, std::string path, std::string version, std::string iconPath);

	void approximateEngineType();

	void detectModsFolder();

	void detectAddonsFolder();
};