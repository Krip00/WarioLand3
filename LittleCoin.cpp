#include "LittleCoin.h"
#include "Sprites.h"
#include "Wario.h"
#include "Game.h"
#include "Sounds.h"

using namespace WL3;

LittleCoin::LittleCoin(QPointF pos, int z) : Spawnable(pos)
{
    _texture[0] = Sprites::instance()->get("lil_coin-0");
    _texture[1] = Sprites::instance()->get("lil_coin-1");
    _texture[2] = Sprites::instance()->get("lil_coin-2");
    _texture[3] = Sprites::instance()->get("lil_coin-3");
    _texture[4] = Sprites::instance()->get("lil_coin-4");
    _texture[5] = Sprites::instance()->get("lil_coin-5");
    setPixmap(_texture[0]);
    schedule("flash_coin", FPS * 4, [this]()
    {
        _flashing = true;
        schedule("del_coin", FPS * 2, [this]() { setVisible(false); });
    });

    setY(pos.y() - TILE);
    setZValue(z);

    spawn();
}

bool LittleCoin::hit(Object* what, Direction fromDir)
{
    Wario* wario = what->to<Wario*>();
    _vel.x = 0;
    if (wario)
    {
        setVisible(false);
        wario->setLittleCoins();
        wario->setUnit();
        wario->increase_total();
        Sounds::instance()->play("get_coin");
        return true;
    }
    return false;
}

bool LittleCoin::animate()
{
    _animation_counter++;
    setPixmap(_texture[(_animation_counter / 5) % 5]);

    if (_flashing)
        setPixmap(_texture[(_animation_counter / 5) % 6]);

    return true;
}

void LittleCoin::spawn()
{
    _y_gravity = 0.1;
    _vel.y = 0;
    _collidable = true;
}
