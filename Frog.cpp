#include "Frog.h"
#include "Sprites.h"
#include "Wario.h"

using namespace WL3;

Frog::Frog(QPointF pos, Direction movingDir) : Enemy(pos, movingDir)
{
    // attributi
    _collidable = true;
    _compenetrable = false;
    _wario_on = false;
    setZValue(30);

    // sprites
    _texture[0] = Sprites::instance()->get("frog-0");
    _texture[1] = Sprites::instance()->get("frog-1");
    _texture[2] = Sprites::instance()->get("frog-2");
    _texture[3] = Sprites::instance()->get("frog-3");
    _texture[4] = Sprites::instance()->get("frog-4");
    _texture[5] = Sprites::instance()->get("frog-5");
    _texture[6] = Sprites::instance()->get("frog-6");
    _texture[7] = Sprites::instance()->get("frog-7");
    _texture[8] = Sprites::instance()->get("frog-8");
    _texture[9] = Sprites::instance()->get("frog-9");

    for (int i = 0; i < 28; i++)
        _texture_angry[i] = Sprites::instance()->get("frog_angry-" + std::to_string(i));



    setPixmap(_texture[0]);
    setY(y() - 43);
    _y_gravity = 0;
}

bool Frog::hit(Object* what, Direction fromDir)
{
    if (_dead)
        return true;

    Wario* wario = what->to<Wario*>();

    if (wario)
    {
        _wario_on = true;
        schedule("wario_not_on_frog", 3, [this]() {_wario_on = false; _animation_counter = 0; });
        if (wario->crouch() && !wario->is_on_pre_fire() && !wario->is_on_fire() && !wario->is_run() && wario->vel().x==0)
        {
            _compenetrable = true;
            schedule("wario_not_comp", 3, [this]() {_compenetrable = false; });

        }
        return true;
    }

    return false;
}

bool Frog::animate()
{
    _animation_counter++;
    setPixmap(_texture[(_animation_counter / 30) % 10]);


    if (is_on())
        setPixmap(_texture_angry[((_animation_counter / 7) % 28)]);
    return true;
}

QPainterPath Frog::shape() const
{
    QPainterPath path;

    path.addRect(0, 27, 32, 21);
    return path;
}
