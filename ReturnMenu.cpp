#include "ReturnMenu.h"
#include "Sprites.h"
#include "Game.h"

using namespace WL3;

ReturnMenu::ReturnMenu(QPointF pos, int z) : Spawnable(pos)
{
    _texture[0] = Sprites::instance()->get("return-1");
    _texture[1] = Sprites::instance()->get("return-2");
    _texture[2] = Sprites::instance()->get("return-3");
    _texture[3] = Sprites::instance()->get("return-4");
    _texture[4] = Sprites::instance()->get("return-5");
    _texture[5] = Sprites::instance()->get("return-6");
    setPixmap(_texture[0]);

    setY(pos.y() - TILE);
    setZValue(z);

    spawn();
}

bool ReturnMenu::animate()
{
    _animation_counter++;
    setPixmap(_texture[(_animation_counter / 6) % 6]);
    return true;
}

void ReturnMenu::spawn()
{
    _y_gravity = 0;
    _vel.y = 0;
    _collidable = true;
}
