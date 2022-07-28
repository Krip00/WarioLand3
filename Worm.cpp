#include "Worm.h"
#include "Sprites.h"
#include "Wario.h"
#include "Sounds.h"
#include "Block.h"
#include "Lift.h"
#include "Game.h"

using namespace WL3;

Worm::Worm(QPointF pos, Direction movingDir) : Enemy(pos, movingDir)
{
    // attributi
    _attack = false;
    _check_attack = false;

    // sprites
    _texture_walk[0] = Sprites::instance()->get("worm_walk-0");
    _texture_walk[1] = Sprites::instance()->get("worm_walk-1");
    _texture_walk[2] = Sprites::instance()->get("worm_walk-2");

    _texture_attack[0] = Sprites::instance()->get("worm_attack-0");
    _texture_attack[1] = Sprites::instance()->get("worm_attack-1");
    _texture_attack[2] = Sprites::instance()->get("worm_attack-2");

    _texture_roll[0] = Sprites::instance()->get("worm_roll-0");
    _texture_roll[1] = Sprites::instance()->get("worm_roll-1");
    _texture_roll[2] = Sprites::instance()->get("worm_roll-2");

    _texture_smashed = Sprites::instance()->get("worm_smashed");

    setPixmap(_texture_walk[0]);
    setY(y() - 16);
    setZValue(50);
}


bool Worm::animate()
{
    _animation_counter++;
    setPixmap(_texture_walk[(_animation_counter / 9) % 3]);

    if (_smashed)
        setPixmap(_texture_smashed);
    else if (_bouncing)
    {
        if (((_animation_counter / 10) % 2) == 1)
            setPixmap(_texture_roll[2]);
        else
            setPixmap(_texture_roll[0]);
    }
    else if (_kicked || _upsidedown)
        setPixmap(_texture_roll[(_animation_counter / 35) % 2]);

    // y-mirroring
    if (_attack && !_upsidedown)
        setPixmap(_texture_attack[(_animation_counter / 9) % 3]);

    // x-mirroring
    if (_vel.x >= 0)
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));


    return true;
}


bool Worm::hit(Object* what, Direction fromDir)
{
    if (_dead)
        return true;

    Wario* wario = what->to<Wario*>();
    StaticObject* stc_obj = what->to<StaticObject*>();
    DynamicObject* dyn_obj = what->to<DynamicObject*>();
    Lift* lift = what->to<Lift*>();
    Block* block = what->to<Block*>();

    if ((lift || stc_obj || (block && block->type() == Block::Type::BRICK)) && fromDir == Direction::DOWN)
        _on_lift = true;
    if ((stc_obj || (dyn_obj && !dyn_obj->compenetrable() /*&& (!_kicked || !_upsidedown)*/)) &&
        (fromDir == Direction::LEFT || fromDir == Direction::RIGHT))
    {
        move(inverse(_x_dir));
        if (_kicked || _upsidedown)
        {
            if (_x_dir == Direction::RIGHT)
                bounce(false, true);
            else if (_x_dir == Direction::LEFT)
                bounce(true, true);
        }
        return true;
    }
    else if (_smashed && (stc_obj || (dyn_obj && !dyn_obj->compenetrable())))
    {
        move(Direction::NONE);
        return true;
    }
    else if (wario)
    {
        // se il nemico e' sottosopra ==> bounce
        if ((wario->is_run() && _upsidedown) || (wario->worm() || wario->thunder() || wario->is_on_fire() || wario->rool()))
            smash(wario);
        else if (fromDir == Direction::UP || fromDir == Direction::DOWN || _upsidedown)
        {
            _attack = false;
            _check_attack = true;
            schedule("check_Att", 30, [this]() {_check_attack = false; });
            Sounds::instance()->play("bump");
            if (_upsidedown && (wario->is_run() || wario->worm() || wario->thunder() || wario->is_on_fire() || wario->rool()))
                smash(wario);
            else if (fromDir == Direction::LEFT)
                bounce(true); // bounce verso destra
            else
                bounce(false);// bounce verso sinistra
        }
        else if (_x_dir != fromDir) // entrambi nella stessa direzione, TAMPONAMENTO
        {
            _attack = false;
            _check_attack = true;
            schedule("check_Att", 30, [this]() {_check_attack = false; });
            if (_upsidedown && (wario->is_run() || wario->worm() || wario->thunder() || wario->is_on_fire() || wario->rool()))
                smash(wario);
            else if (wario->is_run())
                smash(wario);
            else if (_x_dir == Direction::RIGHT)
                bounce(true);
            else
                bounce(false);
        }
        else // FRONTALE, _x_dir == fromDir
        {
            // calcio da destra ==> va a sinistra
            if (_attack)
                wario->pre_worm(true);

            else if (_x_dir == Direction::LEFT)
                bounce(true); // bounce verso destra
            else
                bounce(false);
            _attack = false;
            _check_attack = true;
            schedule("check_Att", 30, [this]() {_check_attack = false; });
        }
        return true;
    }
    return false;
}




void Worm::advance()
{
    Enemy::advance();

    if (upsidedown() && !_bouncing)
        _x_vel_max = 0;
    if (std::abs(Game::instance()->wario()->y() - y() + 22) <= 5 && !_attack && !_check_attack && !upsidedown())
    {

        _check_attack = true;
        schedule("check_Att", 30, [this]() {_check_attack = false; });

        if (Game::instance()->wario()->x() < x() && _x_dir == Direction::RIGHT)
            _x_dir = Direction::LEFT;
        else if (Game::instance()->wario()->x() > x() && _x_dir == Direction::LEFT)
            _x_dir = Direction::RIGHT;
        else if (Game::instance()->wario()->x() < x() || Game::instance()->wario()->x() > x())
            _attack = true;
    }


    if (_attack && _vel.x < 0.3)
        schedule("falseattack", 3, [this]() {_attack = false; });



}


QPainterPath Worm::shape() const
{
    QPainterPath path;
    path.addRect(5, 9, 15, 8);
    return path;
}
