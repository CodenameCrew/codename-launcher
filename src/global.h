#pragma once

#include "engine.h"
#include "raylib.h"
#include <string>
#include <sys/wait.h>
#include <unistd.h>

const char *BOOL_STR(bool b); // genuinely pisses me off
std::vector<std::string> split(std::string s, std::string delimiter);

#define DEBUGMODE false
#define DEFAULTFONT ASSETS_PATH "fonts/Roboto-Regular.ttf"
#define DEFAULTFONTBOLD ASSETS_PATH "fonts/Roboto-Bold.ttf"

#define PRIMARYCOLOR                                                                                                                       \
	CLITERAL(Color)                                                                                                                    \
	{                                                                                                                                  \
		178, 101, 189, 255                                                                                                         \
	}
#define SECONDARYCOLOR                                                                                                                     \
	CLITERAL(Color)                                                                                                                    \
	{                                                                                                                                  \
		137, 72, 165, 255                                                                                                          \
	}
#define BACKGROUNDPRIMARYCOLOR                                                                                                             \
	CLITERAL(Color)                                                                                                                    \
	{                                                                                                                                  \
		45, 30, 50, 255                                                                                                            \
	}
#define BACKGROUNDSECONDARYCOLOR                                                                                                           \
	CLITERAL(Color)                                                                                                                    \
	{                                                                                                                                  \
		33, 22, 37, 255                                                                                                            \
	}
#define LISTCOLOR                                                                                                                          \
	CLITERAL(Color)                                                                                                                    \
	{                                                                                                                                  \
		21, 14, 23, 255                                                                                                            \
	}

void openFolderInExplorer(const char *path);

std::string getDataFolder();
std::string getPath(std::string path);
std::string findExecutable(std::string searchPath);

std::string detectConsoleEmulator();
void executeProgram(std::string path, std::string executable, bool allocateConsole, Engine *engine = nullptr);

extern int curCursorState;