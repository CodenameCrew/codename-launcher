#pragma once
#include <vector>
#include <string>

enum ModType
{
	MOD,
	ADDON
};

struct Mod
{
	std::string name;
	std::string rawName;
	std::string version;
	std::string description;

	ModType type = MOD;

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

	const std::vector<Mod> mods = {};

	Engine(std::string name, std::string path, std::string version, std::string iconPath);

	void approximateEngine();

	void detectModsFolder();

	void detectAddonsFolder();
};