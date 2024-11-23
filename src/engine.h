#pragma once
#include <vector>

enum ModType
{
	MOD,
	ADDON
};

struct Mod
{
	const char *name;
	const char *rawName;
	const char *version;
	const char *description;

	ModType type = MOD;

	const char *pageLink;
};

class Engine
{
public:
	const char *name;
	const char *description;

	const char *rawName;
	const char *path;
	const char *modsPath;
	const char *addonsPath;
	const char *iconPath;

	const char *version;

	const std::vector<Mod> mods = {};

	Engine(const char *name, const char *path, const char *version, const char *iconPath);

	void approximateEngine();

	void detectModsFolder();

	void detectAddonsFolder();
};