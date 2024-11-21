#include "global.h"

#if defined(__linux__)
void openFolderInExplorer(const char* path) {
	system("xdg-open .");
}
#elif defined(_WIN32)
void openFolderInExplorer(const char* path) {
	system("explorer ./");
}
#elif defined(__APPLE__)
void openFolderInExplorer(const char* path) {
	system("open .");
}
#endif