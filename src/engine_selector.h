#include "raylib.h"
#include "ui/container.h"
#include "ui/sprite.h"
#include "ui/text.h"

class EngineContainer : public Container
{
public:
    const char *name;
    const char *path;
    const char *version;

    Sprite *spriteicon;
    Text *textname;
    Text *textversion;

    EngineContainer(const char *enginename, Texture2D engineicon, const char *engineversion, const char *folderpath);

    void draw();
};

class EngineSelector : public Container
{
public:
    EngineSelector();

    void update(float elapsed);

    void draw();
};