#include "Sprites.h"
#include "Game.h"
#include "MenuNumber.h"
using namespace WL3;

MenuNumber::MenuNumber(QPointF pos, int c, int z) : Spawnable(pos)
{
    this->num = c;
    switch (c)
    {
    case 0:
        _menu_number[0] = Sprites::instance()->get("menu_number-0");
        setPixmap(_menu_number[0]);
        break;
    case 1:
        _menu_number[1] = Sprites::instance()->get("menu_number-1");
        setPixmap(_menu_number[1]);
        break;
    case 2:
        _menu_number[2] = Sprites::instance()->get("menu_number-2");
        setPixmap(_menu_number[2]);
        break;
    case 3:
        _menu_number[3] = Sprites::instance()->get("menu_number-3");
        setPixmap(_menu_number[3]);
        break;
    case 4:
        _menu_number[4] = Sprites::instance()->get("menu_number-4");
        setPixmap(_menu_number[4]);
        break;
    case 5:
        _menu_number[5] = Sprites::instance()->get("menu_number-5");
        setPixmap(_menu_number[5]);
        break;
    case 6:
        _menu_number[6] = Sprites::instance()->get("menu_number-6");
        setPixmap(_menu_number[6]);
        break;
    case 7:
        _menu_number[7] = Sprites::instance()->get("menu_number-7");
        setPixmap(_menu_number[7]);
        break;
    case 8:
        _menu_number[8] = Sprites::instance()->get("menu_number-8");
        setPixmap(_menu_number[8]);
        break;
    case 9:
        _menu_number[9] = Sprites::instance()->get("menu_number-9");
        setPixmap(_menu_number[9]);
        break;
    }

    setY(pos.y() - TILE);
    setZValue(z);

    spawn();
}

void MenuNumber::spawn()
{
    _y_gravity = 0;
    _vel.y = 0;
    _collidable = false;
}

QPixmap MenuNumber::get()
{
    return _menu_number[this->num];
}
