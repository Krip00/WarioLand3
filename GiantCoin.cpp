#include "GiantCoin.h"
#include "Sprites.h"
#include "Wario.h"
#include "Game.h"
#include "Sounds.h"

using namespace WL3;

GiantCoin::GiantCoin(QPointF pos, int z) : Spawnable(pos)
{
    _texture[0] = Sprites::instance()->get("coin-0");
    _texture[1] = Sprites::instance()->get("coin-1");
    _texture[2] = Sprites::instance()->get("coin-2");
    _texture[3] = Sprites::instance()->get("coin-3");
    _texture[4] = Sprites::instance()->get("coin-4");
    _texture[5] = Sprites::instance()->get("coin-5");
    _texture[6] = Sprites::instance()->get("coin-6");
    _texture[7] = Sprites::instance()->get("coin-7");
    _texture[8] = Sprites::instance()->get("coin-8");
    _texture[9] = Sprites::instance()->get("coin-9");
    _texture[10] = Sprites::instance()->get("coin-10");
    _texture[11] = Sprites::instance()->get("coin-11");
    setPixmap(_texture[0]);

    setY(pos.y() - TILE);
    setZValue(z);

    spawn();
}

bool GiantCoin::hit(Object* what, Direction fromDir)
{
    Wario* wario = what->to<Wario*>();

    if (wario)
    {
        setVisible(false);
        wario->setCoins();
        wario->increase_total(true);
        Sounds::instance()->play("get_coin");
        return true;
    }
    return false;
}

bool GiantCoin::animate()
{
    _animation_counter++;

    setPixmap(_texture[(_animation_counter / 11) % 11]);

    return true;
}

void GiantCoin::spawn()
{
    _y_gravity = 0;
    _vel.y = 0;
    _collidable = true;
}
