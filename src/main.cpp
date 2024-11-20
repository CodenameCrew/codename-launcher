/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you
--  wrote the original software. If you use this software in a product, an acknowledgment
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#pragma GCC diagnostic push

#include "engine_selector.h"
#include "global.h"
#include "raylib.h"
#include "ui/button.h"
#include "ui/container.h"
#include "ui/sprite.h"
#include "ui/text.h"
#include <math.h>
#include <stdio.h>
#include <vector>

std::vector<Object *> children = {};
void add(Object *child)
{
	children.push_back(child);
}

Vector2 mousePosition = {-100.0f, -100.0f};

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(1280, 720, "Hello Raylib");

	EngineSelector *here = new EngineSelector();
	add(here);

	while (!WindowShouldClose())
	{
		mousePosition = GetMousePosition();
		for (auto child : children)
		{
			child->update(GetFrameTime());
		}

		BeginDrawing();
		ClearBackground(BACKGROUNDPRIMARYCOLOR);

		// draw some text using the default font
		DrawText("Hello Raylib", 200, 200, 20, GetColor(0xff0000ff));

		for (auto child : children)
		{
			child->draw();
		}

		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
