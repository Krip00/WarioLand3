#include "Chest.h"
#include "Sprites.h"
#include "Game.h"
using namespace WL3;

Chest::Chest(QPointF pos, int z) : Spawnable(pos)
{
    _texture[0] = Sprites::instance()->get("chest-0");
    _texture[1] = Sprites::instance()->get("chest-1");
    _texture[2] = Sprites::instance()->get("chest-2");

    setPixmap(_texture[0]);

    setY(pos.y() - TILE);
    setZValue(z);

    spawn();
}


bool Chest::animate()
{
    _animation_counter++;

    setPixmap(_texture[(_animation_counter / 8) % 3]);

    return true;
}


void Chest::spawn()
{
    _y_gravity = 0;
    _vel.y = 0;
    _collidable = true;
}


QPainterPath Chest::shape() const
{
    QPainterPath path;
    path.addRect(16, 48, 16, 16);
    return path;
}
