#pragma once

#include "raylib.h"
#include <string>

const char *BOOL_STR(bool b); // genuinely pisses me off

#define DEBUGMODE true
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

extern int curCursorState;