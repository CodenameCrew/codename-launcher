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

std::string getPath(std::string path) {
	std::string gotPath = getDataFolder() + path;
	if (DirectoryExists(gotPath.c_str())) gotPath += "/";
	return gotPath;
}

std::string findExecutable(std::string searchPath) {
	TraceLog(LOG_INFO, searchPath.c_str());
	FilePathList executableSearch;
	const char* foundExecutable;
	#if defined(__linux__)
	executableSearch = LoadDirectoryFiles(searchPath.c_str());
	for (auto i = 0; i < (int)executableSearch.count; i++) {
		auto curpath = executableSearch.paths[i];
		if (std::string(GetFileName(curpath)) == std::string(GetFileNameWithoutExt(curpath)) && !DirectoryExists(curpath)) {
			foundExecutable = GetFileName(curpath);
			break;
		}
	}
	#elif defined(_WIN32)
	executableSearch = LoadDirectoryFilesEx(searchPath.c_str(), "exe", false);
	foundExecutable = GetFileName(executableSearch.paths[0]);
	#elif defined(__APPLE__)
	// todo
	#endif

	TraceLog(LOG_INFO, foundExecutable);
	return foundExecutable;
}