#pragma once

#include "global.h"
#include "raylib.h"
#include "ui/button.h"
#include "ui/container.h"
#include "ui/sprite.h"
#include "ui/text.h"
#include "engine_selector.h"
#include <math.h>
#include <stdio.h>
#include <vector>

extern std::vector<Object *> mainchildren;
void addToMain(Object *child);