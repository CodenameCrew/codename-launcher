class Engine {
	public:
	const char *name;

    const char *rawName;
	const char *path;
	const char *modsPath;
	const char *addonsPath;
	const char *iconPath;

	const char *version;

	Engine(const char* name, const char* path, const char* version, const char* iconPath);

	void approximateEngine();

	void detectModsFolder();

	void detectAddonsFolder();
};

enum ModType {
    MOD,
    ADDON
};

typedef struct Mod {
    const char* name;
    const char* rawName;
    const char* version;
    const char* description;

    ModType type = MOD;

    const char* pageLink;
};