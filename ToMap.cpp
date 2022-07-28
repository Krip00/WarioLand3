#include "ToMap.h"
#include "Sprites.h"
#include "Game.h"

using namespace WL3;

ToMap::ToMap(QPointF pos, int z) : Spawnable(pos)
{
    _texture[0] = Sprites::instance()->get("to_map-1");
    _texture[1] = Sprites::instance()->get("to_map-2");
    _texture[2] = Sprites::instance()->get("to_map-3");
    _texture[3] = Sprites::instance()->get("to_map-4");
    _texture[4] = Sprites::instance()->get("to_map-5");
    setPixmap(_texture[0]);

    setY(pos.y() - TILE);
    setZValue(z);

    spawn();
}

bool ToMap::animate()
{
    _animation_counter++;

    setPixmap(_texture[(_animation_counter / 8) % 5]);

    return true;
}

void ToMap::spawn()
{
    _y_gravity = 0;
    _vel.y = 0;
    _collidable = true;
}
