#pragma once

#include "engine.h"
#include "engine_overview.h"
#include "engine_selector.h"
#include "global.h"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"
#include "raylib.h"
#include "ui/button.h"
#include "ui/container.h"
#include "ui/sprite.h"
#include "ui/text.h"
#include <math.h>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <vector>

extern std::vector<Object *> mainchildren;
extern std::vector<Engine *> engines;
extern EngineSelector *leftPanel;
extern EngineOverview *rightPanel;
extern int engineJsonLastSize;
void checkFiles();
int parseEngines();
void checkForChanges();

void addToMain(Object *child);