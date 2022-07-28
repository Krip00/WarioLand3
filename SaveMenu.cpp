#include "SaveMenu.h"
#include "Sprites.h"
#include "Game.h"

using namespace WL3;

SaveMenu::SaveMenu(QPointF pos, int z) : Spawnable(pos)
{
    _texture[0] = Sprites::instance()->get("save-1");
    _texture[1] = Sprites::instance()->get("save-2");
    _texture[2] = Sprites::instance()->get("save-3");
    _texture[3] = Sprites::instance()->get("save-4");
    setPixmap(_texture[0]);

    setY(pos.y() - TILE);
    setZValue(z);

    spawn();
}

bool SaveMenu::animate()
{
    _animation_counter++;

    setPixmap(_texture[(_animation_counter / 10) % 4]);

    return true;
}

void SaveMenu::spawn()
{
    _y_gravity = 0;
    _vel.y = 0;
    _collidable = true;
}
