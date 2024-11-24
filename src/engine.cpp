#include "engine.h"

Engine::Engine(std::string name, std::string path, std::string version, std::string iconPath) {
    this->name = name;
	this->version = version;
	this->iconPath = iconPath;
    this->path = path;
    rawName = findExecutable(path);
}