#include "Enemy.h"
#include "Spark.h"
#include "Wario.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Game.h"
#include "Block.h"

using namespace WL3;

Spark::Spark(QPointF pos, Direction movingDir) : Enemy(pos, movingDir)
{
    // attributes
    _check_spawn = false;
    _collidable = true;
    _compenetrable = true;
    _hit = false;

    // sprites
    _spark[0] = Sprites::instance()->get("spark-0");
    _spark[1] = Sprites::instance()->get("spark-1");
    _spark[2] = Sprites::instance()->get("spark-2");
    _spark[3] = Sprites::instance()->get("spark-3");

    _vanish[0] = Sprites::instance()->get("spark-4");
    _vanish[1] = Sprites::instance()->get("spark-5");
    _vanish[2] = Sprites::instance()->get("spark-6");

    setPixmap(_spark[0]);
    setY(y() - 16);

    _y_gravity = 0.01;
}

void Spark::stop_spark() {
    _x_vel_min = 0;
    _x_vel_max = 0;
    _y_vel_max = 0;
    _y_vel_min = 0;
    _y_gravity = 0;
}

bool Spark::hit(Object* what, Direction fromDir)
{
    Enemy* enemy = what->to<Enemy*>();
    Block* block = what->to<Block*>();
    Wario* wario = what->to<Wario*>();



    if (enemy || _dead || (block && block->type() == Block::Type::HIDDEN))
        return false;

    if (wario && (!wario->is_on_pre_fire() && !wario->is_on_fire()))
        Sounds::instance()->play("thunder_1");

    // quando hitta si ferma sul posto
    stop_spark();

    if (!wario)
        _dead = true;
    schedule("hitting", 25, [this]() {setVisible(false); });
    _animation_counter = -1;


    Enemy::hit(what, fromDir);

    return false;
}

bool Spark::animate()
{
    _animation_counter++;
    setPixmap(_spark[(_animation_counter / 8) % 4]);

    if (_dead)
        setPixmap(_vanish[(_animation_counter / 18) % 3]);


    return false;
}

void Spark::advance()
{
    Enemy::advance();

    if (!_check_spawn)
    {
        _check_spawn = true;
        if (Game::instance()->wario()->x() < x())
            _x_dir = Direction::LEFT;
        else if (Game::instance()->wario()->x() > x())
            _x_dir = Direction::RIGHT;
        else
            _x_dir = Direction::NONE;

        schedule("SparkDirection", 6 * 10, [this]() {_check_spawn = false; });
    }
}

QPainterPath Spark::shape() const
{
    QPainterPath path;

    path.addRect(6, 6, 5, 5);
    return path;
}
