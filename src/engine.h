#pragma once
#include <string>
#include <vector>

enum ModType
{
	MOD,
	ADDON
};

enum EngineType
{
	PSYCH,
	CODENAME,
	VSLICE,
	FPSPLUS,
	OTHER,
	UNKNOWN
};

struct Stats
{
	std::string storage;
	std::string modsStorage;
	std::string lastUpdated;
};

class Mod
{
public:
	std::string name;
	std::string version;
	std::string description;
	std::string storage;

	std::string path;

	ModType type = MOD;
	EngineType supportType;

	Mod();

	Mod(std::string name,
	    std::string version,
	    std::string description,
	    std::string path,
	    ModType type = MOD,
	    EngineType supportType = OTHER);

	void approximateModType();

	std::string pageLink;
};

class Engine
{
public:
	std::string name;
	std::string version;
	std::string description;

	std::string rawName;
	std::string path;
	std::string modsPath;
	std::string addonsPath;
	std::string iconPath;
	std::string executeCommand;

	Stats stats;
	EngineType type;

	std::vector<Mod *> mods = {};
	std::vector<std::string> features;

#if defined(_WIN32)
	PROCESS_INFORMATION _processPid;
#elif defined(__linux__) || defined(__APPLE__)
	pid_t _processPid;
#endif

	Engine();
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

	void loadData();

	void approximateEngineType();

	void detectModsFolder();

	void detectAddonsFolder();
};
