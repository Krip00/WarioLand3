#include "Enemy.h"
#include "Wario.h"
#include "Lift.h"
#include "Sounds.h"
#include "Block.h"

using namespace WL3;

Enemy::Enemy(QPointF pos, Direction movingDir) : DynamicObject(pos)
{
    // attributi di default
    _start = true;
    _bouncing = false;
    _gliding = false;
    _temp = false;
    _on_lift = false;

    // stati di default
    _smashed = false;
    _kicked = false;
    _awakening = false;
    _upsidedown = false;
    _dead = false;

    // fisica di default
    _x_vel_max = 0.5;
    move(movingDir);

    setZValue(3);
}

void Enemy::advance()
{
    if (_start && !_temp)
    {
        _temp = true;
        schedule("started", 30, [this]() {_start = false; });
    }
    if (_start && !_gliding && !_upsidedown && !_awakening && !_kicked)
    {
        _vel.x = 0.5;
        _x_vel_max = 0.5;
    }
    else if (_upsidedown)
        _vel.x = 0;


    DynamicObject::advance();

    if (((_prev_vel.y == 0 && _vel.y > 0 
        && !_gliding && !_upsidedown && !_awakening && !_kicked && !_smashed) || _on_lift) && !_start)
    {
        setY(y() - _vel.y);
        _vel.y = -_vel.y;
        if (_on_lift) {
            _vel.y = 0;
            schedule("onlift", 3, [this]() {_vel.y = 0.1; _prev_vel.y = 0.001; });

        }

        _gliding = true;
        schedule("gliding", 3, [this]() {_gliding = false; });
    }
    if (_gliding && _vel.y > 0 && !_upsidedown && !_kicked && !_awakening && !_kicked && !_smashed) {
        setY(y() - _vel.y);
        _vel.y = -_vel.y;
        move_on_board();
    }
    _on_lift = false;
}



bool Enemy::hit(Object* what, Direction fromDir)
{
    if (_dead)
        return true;

    StaticObject* stc_obj = what->to<StaticObject*>();
    DynamicObject* dyn_obj = what->to<DynamicObject*>();
    Lift* lift = what->to<Lift*>();
    Block* block = what->to<Block*>();

    if ((lift || stc_obj || (block && block->type() == Block::Type::BRICK)) && fromDir == Direction::DOWN)
        _on_lift = true;

    else if (_smashed && (stc_obj || (dyn_obj && !dyn_obj->compenetrable())))
    {
        move(Direction::NONE);
        return true;
    }


    return false;
}

void Enemy::smash(DynamicObject* what)
{
    if (_smashed)
        return;
    _smashed = true;
    _upsidedown = true;
    Sounds::instance()->play("kill_enemy");


    Wario* wario = what->to<Wario*>();

    if (wario)
    {
        if (wario->x_vel_last_nonzero() > 0)
            _x_dir = Direction::RIGHT;
        else
            _x_dir = Direction::LEFT;

        // smash physics
        _x_vel_min = 3;
        _y_gravity = 0.1;
        _vel.y = -2.0;
        _dead = true;
        _collidable = false;
        schedule("die-smash", 5 * 60, [this]() {setVisible(false); });
        return;

    }
}


void Enemy::kick(bool right, int force)
{
    if (right)
        move(Direction::RIGHT);
    else
        move(Direction::LEFT);
    if (_kicked)
        bounce(right);
    _kicked = true;
    _x_vel_max = force;
    _schedulers.erase("stop_mov");
    schedule("willhurt", 15, [this, right, force]()
        {
            _kicked = false;
            _prev_vel.y = 0.0001;
            _vel.y = 0.0001;
            _x_vel_max = 0.5;
            _x_dir = Direction::NONE;
            schedule("move", 5, [this, right, force]() {
                if (force == 2)
                    move(!right ? Direction::RIGHT : Direction::LEFT);
                else
                    move(right ? Direction::RIGHT : Direction::LEFT); });
        });

}

void Enemy::bounce(bool right, bool wall)
{
    if (!right && wall)
        move(Direction::RIGHT);
    else if (right && !wall)
        move(Direction::RIGHT);
    else
        move(Direction::LEFT);
    _schedulers.erase("move");
    _schedulers.erase("willhurt");
    _schedulers.erase("get_back");
    _schedulers.erase("up");
    _schedulers.erase("stop_mov");
    _kicked = false;
    _upsidedown = true;
    _bouncing = true;
    _y_gravity = 0.15;
    _vel.y = -2.0;
    _x_vel_max = 2.8;
    schedule("get_back", 5, [this, right]()
        {
            _y_gravity = 0.4375;
            _x_vel_max = 0;
            _vel.y = 0;
            _bouncing = false;
            schedule("up", 200, [this, right]()
                {
                    _upsidedown = false;
                    _x_vel_min = 0.5;
                    _x_vel_max = 0.5;
                });
        });
    Sounds::instance()->play("kick");
}

void Enemy::move_on_board()
{
    if (_x_dir == Direction::RIGHT)
        setX(x() - 1);
    else
        setX(x() + 1);

    _x_vel_max = 0.00001;
    schedule("change_vel", 50, [this]()
        {
            _x_vel_max = 0.5;
            invertDir();
            schedule("vel-y", 3, [this]() {_prev_vel.y = 0.0001; _vel.y = 0.0001; });
        });
}
