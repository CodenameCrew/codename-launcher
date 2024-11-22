#include "global.h"

const char *BOOL_STR(bool b)
{
	return b ? "true" : "false";
}

#if defined(__linux__)
void openFolderInExplorer(const char *path)
{
	system(("xdg-open \"" + std::string(path) + "\"").c_str());
}
std::string getDataFolder()
{
	std::string homedir = getenv("HOME");
	homedir.append("/.config/codename-launcher/");
	return homedir;
}
#elif defined(_WIN32)
void openFolderInExplorer(const char *path)
{
	system(("explorer \"" + std::string(path) + "\"").c_str());
}
std::string getDataFolder()
{
	std::string appdatadir = getenv("LOCALAPPDATA");
	appdatadir.append("\\CodenameLauncher");
	return appdatadir;
}
#elif defined(__APPLE__)
void openFolderInExplorer(const char *path)
{
	system(("open \"" + std::string(path) + "\"").c_str());
}
std::string getDataFolder()
{
	std::string homedir = getenv("HOME");
	homedir.append("/Library/Application Support/Codename Launcher/");
	return homedir;
}
#endif

int curCursorState = 1;