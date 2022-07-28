#include "Fireball.h"
#include "Enemy.h"
#include "Sprites.h"
#include "Wario.h"

using namespace WL3;

Fireball::Fireball(QPointF pos, Direction movingDir, double vely) : Enemy(pos, movingDir)
{
    // attributi
    _collidable = true;
    _compenetrable = true;

    // sprites
    _fireball[0] = Sprites::instance()->get("fireball-0");
    _fireball[1] = Sprites::instance()->get("fireball-1");

    _vanish[0] = Sprites::instance()->get("fireball-2");
    _vanish[1] = Sprites::instance()->get("fireball-3");

    setPixmap(_fireball[0]);
    setY(y() - 16);
    _y_gravity = vely;
}


bool Fireball::hit(Object* what, Direction fromDir)
{
    Wario* wario = what->to<Wario*>();
    Enemy* enemy = what->to<Enemy*>();


    if (enemy || _dead)
        return false;
    // quando hitta si ferma sul posto

    _x_vel_min = 0;
    _x_vel_max = 0;
    _y_vel_max = 0;
    _y_vel_min = 0;
    _y_gravity = 0;
    _dead = true;
    schedule("hitting", 14, [this]() {setVisible(false); });
    _animation_counter = 0;

    if (wario && !wario->worm() && !wario->is_on_pre_fire() && !wario->is_on_fire() && !wario->bumped())
    {
        wario->pre_fire(true);
        return true;
    }


    return false;
}

bool Fireball::animate()
{
    _animation_counter++;
    setPixmap(_fireball[(_animation_counter / 8) % 2]);

    if (_dead)
        setPixmap(_vanish[(_animation_counter / 8) % 2]);


    return false;
}

QPainterPath Fireball::shape() const
{
    QPainterPath path;

    path.addRect(6, 6, 5, 5);
    return path;
}
