#include "global.h"

#if defined(__linux__)
void openFolderInExplorer(const char* path) {
	system(("xdg-open \"" + std::string(path) + "\"").c_str());
}
const char* getDataFolder() {
	return "~/.config/codename-launcher/";
}
#elif defined(_WIN32)
void openFolderInExplorer(const char* path) {
	system(("explorer \"" + std::string(path) + "\"").c_str());
}
const char* getDataFolder() {
	return getenv("LOCALAPPDATA") + "/CodenameLauncher";
}
#elif defined(__APPLE__)
void openFolderInExplorer(const char* path) {
	system(("open \"" + std::string(path) + "\"").c_str());
}
const char* getDataFolder() {
	return "~/Library/Application Support/Codename Launcher/";
}
#endif