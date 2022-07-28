#include "LittleKey.h"
#include "Sprites.h"
#include "Wario.h"
#include "Game.h"

using namespace WL3;

LittleKey::LittleKey(QPointF pos, Key::Color c) : Key(pos, c)
{
    if (c == Color::GREY)
        _texture[0] = Sprites::instance()->get("lil_key-grey");
    if (c == Color::GREEN)
        _texture[0] = Sprites::instance()->get("lil_key-green");
    if (c == Color::RED)
        _texture[0] = Sprites::instance()->get("lil_key-red");
    if (c == Color::BLUE)
        _texture[0] = Sprites::instance()->get("lil_key-blue");

    setY(pos.y() - TILE);
    setZValue(999);

    setPixmap(_texture[0]);
    spawn();
}

bool LittleKey::hit(Object* what, Direction fromDir)
{
    return false;
}

bool LittleKey::animate()
{
    return true;
}

void LittleKey::spawn()
{
    _y_gravity = 0;
    _vel.y = 0;
    _collidable = false;
}
