#include "Spider.h"
#include "Sprites.h"
#include "Wario.h"
#include "Spark.h"

using namespace WL3;

Spider::Spider(QPointF pos, Direction movingDir) : Enemy(pos, movingDir)
{
    // attributes
    _collidable = true;
    _compenetrable = true;
    _spawn_count = 0;
    _check_spawn = false;

    // textures
    primary_texture[0] = Sprites::instance()->get("spider-0");
    primary_texture[1] = Sprites::instance()->get("spider-1");
    primary_texture[2] = Sprites::instance()->get("spider-2");
    primary_texture[3] = Sprites::instance()->get("spider-3");
    primary_texture[4] = Sprites::instance()->get("spider-4");
    primary_texture[5] = Sprites::instance()->get("spider-5");
    primary_texture[6] = Sprites::instance()->get("spider-6");
    primary_texture[7] = Sprites::instance()->get("spider-7");
    primary_texture[8] = Sprites::instance()->get("spider-8");
    primary_texture[9] = Sprites::instance()->get("spider-9");
    primary_texture[10] = Sprites::instance()->get("spider-10");

    setPixmap(primary_texture[0]);
    setY(y() - 16);
    _y_gravity = 0;
}


QPainterPath Spider::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 23, 15);
    return path;
}

bool Spider::animate()
{
    _animation_counter++;
    setPixmap(primary_texture[(_animation_counter / 22) % 11]);

    return true;
}

void Spider::advance()
{
    Enemy::advance();
    if (!_check_spawn && !_dead)
    {
        _spawn_count++;
        _check_spawn = true;
        new Spark(QPoint(x(), y() + 16), Direction::NONE);
        if (_spawn_count == 4)
        {
            schedule("sparkgenerator", 60 * 10, [this]() {_check_spawn = false; });
            _spawn_count = 0;
        }
        else
            schedule("sparkgenerator", 60 * 2, [this]() {_check_spawn = false; });
    }
}

bool Spider::hit(Object* what, Direction fromDir)
{
    Wario* wario = what->to<Wario*>();

    if (wario && wario->thunder() && !_dead)
    {
        _dead = true;
        move(Direction::NONE);
        _vel.y = 2;
        _compenetrable = true;
        schedule("Togliti", 60 * 2, [this]() {setVisible(false); });
        return true;
    }

    return false;
}
