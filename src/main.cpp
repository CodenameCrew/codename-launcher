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

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "ui/button.cpp"
#include "ui/container.cpp"
#include "ui/sprite.cpp"
#include "ui/text.cpp"
#include <vector>
#include <stdio.h>
#include <math.h>
std::vector<Object*> children = {};
void add(Object* child) {
	children.push_back(child);
}

Vector2 mousePosition = {-100.0f, -100.0f};

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	InitWindow(854, 480, "Hello Raylib");
	SearchAndSetResourceDir("resources");

	Container* containser = new Container(20, 20, 250, 225);
	add(containser);

	Button* thing = new Button(0, 0, 250, 50, GetColor(0xb265bdff));
	containser->add(thing);
	thing->clickCallback = () -> {
		
	}
	Sprite* icon = new Sprite(5, 5, LoadTexture("wabbit_alpha.png"));
	thing->add(icon);
	Text* text = new Text(30, 10, "click to destroy dis fukin bunny", 10);
	thing->add(text);
	Button* thing2 = new Button(0, 50, 250, 50, GetColor(0xb4152dff));
	containser->add(thing2);
	Button* thing3 = new Button(0, 100, 250, 50, GetColor(0x22656dff));
	containser->add(thing3);
	Button* thing4 = new Button(0, 150, 250, 50, GetColor(0xb2d22dff));
	containser->add(thing4);
	Button* thing5 = new Button(0, 200, 250, 50, GetColor(0xb26dbdff));
	containser->add(thing5);
	Button* thing6 = new Button(0, 250, 250, 50, GetColor(0xbd65bdff));
	containser->add(thing6);
	
	while (!WindowShouldClose())
	{

		containser->height = 225 - (sin(GetTime()) * 50);


		mousePosition = GetMousePosition();
		for (auto child : children) {
			child->update(GetFrameTime());
		}

		BeginDrawing();
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20, GetColor(0xff0000ff));

		for (auto child : children) {
			child->draw();
		}
		
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
