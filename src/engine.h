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
public:
	std::string name;
	std::string version;
	std::string description;

	std::string path;

	ModType type = MOD;
	EngineType supportType;

	Mod(
		std::string name,
		std::string version,
		std::string description,
		std::string path,
		ModType type = MOD,
		EngineType supportType = OTHER
	);

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
	std::string executeCommand;

	std::string version;

	EngineType type;

	std::vector<Mod *> mods = {};

	Engine(
		std::string name,
		std::string description,
		std::string rawName,
		std::string path,
		std::string iconPath,
		std::string version,
		EngineType type,
		std::string modsPath = "",
		std::string addonsPath = "",
		std::string executeCommand = ""
	);

	void approximateEngineType();

	void detectModsFolder();

	void detectAddonsFolder();
};

