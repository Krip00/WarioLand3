#include "Key.h"
#include "Sprites.h"
#include "Wario.h"
#include "Game.h"
#include "Sounds.h"
#include "LittleKey.h"
using namespace WL3;

Key::Key(QPointF pos, Key::Color c, int z) : Spawnable(pos)
{
    _c = c;
    if (c == Key::Color::GREY)
    {
        _texture[0] = Sprites::instance()->get("key_grey-0");
        _texture[1] = Sprites::instance()->get("key_grey-1");
        _texture[2] = Sprites::instance()->get("key_grey-2");
        _texture[3] = Sprites::instance()->get("key_grey-3");
        _texture[4] = Sprites::instance()->get("key_grey-4");
        _texture[5] = Sprites::instance()->get("key_grey-5");
        _texture[6] = Sprites::instance()->get("key_grey-6");
        _texture[7] = Sprites::instance()->get("key_grey-7");
    }
    else if (c == Key::Color::GREEN)
    {
        _texture[0] = Sprites::instance()->get("key_green-0");
        _texture[1] = Sprites::instance()->get("key_green-1");
        _texture[2] = Sprites::instance()->get("key_green-2");
        _texture[3] = Sprites::instance()->get("key_green-3");
        _texture[4] = Sprites::instance()->get("key_green-4");
        _texture[5] = Sprites::instance()->get("key_green-5");
        _texture[6] = Sprites::instance()->get("key_green-6");
        _texture[7] = Sprites::instance()->get("key_green-7");
    }
    else if (c == Key::Color::RED)
    {
        _texture[0] = Sprites::instance()->get("key_red-0");
        _texture[1] = Sprites::instance()->get("key_red-1");
        _texture[2] = Sprites::instance()->get("key_red-2");
        _texture[3] = Sprites::instance()->get("key_red-3");
        _texture[4] = Sprites::instance()->get("key_red-4");
        _texture[5] = Sprites::instance()->get("key_red-5");
        _texture[6] = Sprites::instance()->get("key_red-6");
        _texture[7] = Sprites::instance()->get("key_red-7");
    }
    else if (c == Key::Color::BLUE)
    {
        _texture[0] = Sprites::instance()->get("key_blue-0");
        _texture[1] = Sprites::instance()->get("key_blue-1");
        _texture[2] = Sprites::instance()->get("key_blue-2");
        _texture[3] = Sprites::instance()->get("key_blue-3");
        _texture[4] = Sprites::instance()->get("key_blue-4");
        _texture[5] = Sprites::instance()->get("key_blue-5");
        _texture[6] = Sprites::instance()->get("key_blue-6");
        _texture[7] = Sprites::instance()->get("key_blue-7");
    }

    setPixmap(_texture[0]);


    setY(pos.y() - TILE);
    setZValue(z);

    spawn();
}

bool Key::hit(Object* what, Direction fromDir)
{
    Wario* wario = what->to<Wario*>();

    if (wario)
    {
        setVisible(false);
        wario->increase_total(true);
        wario->add_key();

        if (_c == Key::Color::GREY)
            new LittleKey(QPointF(3.13 * TILE, 11.25 * TILE), Key::Color::GREY);
        else if (_c == Key::Color::GREEN)
            new LittleKey(QPointF(5.13 * TILE, 11.25 * TILE), Key::Color::GREEN);
        else if (_c == Key::Color::RED)
            new LittleKey(QPointF(4.13 * TILE, 11.25 * TILE), Key::Color::RED);
        else if (_c == Key::Color::BLUE)
            new LittleKey(QPointF(6.13 * TILE, 11.25 * TILE), Key::Color::BLUE);

        Sounds::instance()->play("get_coin");
        return true;
    }
    return false;
}

bool Key::animate()
{
    _animation_counter++;
    setPixmap(_texture[(_animation_counter / 12) % 8]);
    return true;
}

void Key::spawn()
{
    _y_gravity = 0;
    _vel.y = 0;
    _collidable = true;
}

QPainterPath Key::shape() const
{
    QPainterPath path;
    path.addRect(7, 1, 12, 28);
    return path;
}
