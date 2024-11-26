#pragma once

#include "engine_overview.h"
#include "engine_selector.h"
#include "global.h"
#include "engine.h"
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
#include <vector>

extern std::vector<Object *> mainchildren;
extern std::vector<Engine *> engines;
void checkFiles();
void parseEngines();
void addToMain(Object *child);