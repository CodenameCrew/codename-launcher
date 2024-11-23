#pragma once

#include "engine_overview.h"
#include "engine_selector.h"
#include "global.h"
#include "raylib.h"
#include "ui/button.h"
#include "ui/container.h"
#include "ui/sprite.h"
#include "ui/text.h"
#include "rapidjson.h"
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>

extern std::vector<Object *> mainchildren;
void checkFiles();
void parseEngines();
void addToMain(Object *child);