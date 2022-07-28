#include "SpearHead.h"
#include "Ramp.h"
#include "Sprites.h"
#include "StaticObject.h"
#include "Wario.h"
#include "Sounds.h"
#include "Game.h"

using namespace WL3;

SpearHead::SpearHead(QPointF pos, Direction movingDir) : Enemy(pos, movingDir)
{
    _spawn_point = pos;
    _moving_spearhead = movingDir;
    _wario_hit = false;
    _scripted = false;

    // sprites
    _texture_walk[0] = Sprites::instance()->get("blue_walk-0"); 
    _texture_walk[1] = Sprites::instance()->get("blue_walk-1");
    _texture_smashed = Sprites::instance()->get("blue_smashed"); 
    _texture_upsidedown[0] = Sprites::instance()->get("blue_up-0"); 
    _texture_upsidedown[1] = Sprites::instance()->get("blue_up-1");
    _texture_upsidedown[2] = Sprites::instance()->get("blue_up-2");
    _texture_roll[0] = Sprites::instance()->get("blue_roll-0"); 
    _texture_roll[1] = Sprites::instance()->get("blue_roll-1");
    _texture_roll[2] = Sprites::instance()->get("blue_roll-2");
    _texture_roll[3] = Sprites::instance()->get("blue_roll-3");

    setPixmap(_texture_walk[0]);
}

bool SpearHead::animate()
{
    _animation_counter++;

    setPixmap(_texture_walk[(_animation_counter / 8) % 2]);

    if (_smashed)
        setPixmap(_texture_smashed);
    else if (_upsidedown)
        setPixmap(_texture_upsidedown[(_animation_counter / 8) % 3]);
    else if (_kicked)
        setPixmap(_texture_roll[(_animation_counter / 4) % 4]);

    // x-mirroring
    if (_vel.x >= 0)
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));

    return true;
}

bool SpearHead::hit(Object* what, Direction fromDir)
{
    Wario* wario = what->to<Wario*>();
    StaticObject* stc_obj = what->to<StaticObject*>();
    DynamicObject* dyn_obj = what->to<DynamicObject*>();
    Ramp* ramp = what->to<Ramp*>();


    if ((stc_obj || (dyn_obj && !dyn_obj->compenetrable())) &&
        (fromDir == Direction::LEFT || fromDir == Direction::RIGHT))
    {
        if (_kicked || _upsidedown && !_bouncing)
        {
            if (_x_dir != Direction::RIGHT)
                bounce(false, true);
            else
                bounce(true, true);
        }
        else
        {
            _x_vel_max = 0;
            schedule("pause", 50, [this]() {move(inverse(_x_dir)); _x_vel_max = 0.5; });
        }
        return true;
    }

    else if (wario)
    {
        _wario_hit = true;
        // Hit con fake wario worm
        if (x() <= (117 + 0.5) * TILE && x() >= (115 * TILE - 1) && wario->worm())
        {
            if (_x_dir != fromDir && _x_dir != Direction::UP && _x_dir != Direction::DOWN)
            {
                if (_x_dir == Direction::RIGHT)
                    kick(true);
                else
                    kick(false);
            }
            else if (_x_dir == fromDir)
            {
                if (_x_dir == Direction::RIGHT)
                    kick(false, 2);
                else
                    kick(true, 2);
            }
            return true;
        }

        if (wario->worm() || wario->is_on_fire() || wario->thunder() ||
            wario->rool() || (_upsidedown && wario->is_run())) {
            smash(wario);
            if (wario->is_run() && _upsidedown)
                wario->run(false);
        }
        // se il nemico e' sottosopra ==> bounce
        else if (fromDir == Direction::UP || fromDir == Direction::DOWN || _upsidedown && !_bouncing)
        {
            Sounds::instance()->play("bump");
            if (fromDir == Direction::LEFT)
                bounce(true); // bounce verso destra
            else
                bounce(false);// bounce verso sinistra
        }
        else if (_x_dir != fromDir) // entrambi nella stessa direzione, TAMPONAMENTO, wario colpisce blu
        {
            if (wario->is_run())
            {
                smash(wario);
                wario->run(false);
            }
            else if (_x_dir == Direction::RIGHT)
            {
                Sounds::instance()->play("bump");
                kick(true);
            }
            else
            {
                Sounds::instance()->play("bump");
                kick(false);
            }
        }
        else // FRONTALE, _x_dir == fromDir, blu colpisce wario
        {
            if (!wario->is_on_pre_fire() && !upsidedown())
            {
                _schedulers.erase("exitBump");
                wario->bumped(true);
                Sounds::instance()->play("hit");
            }
            // calcio da destra ==> va a sinistra
            if (_x_dir == Direction::RIGHT)
                kick(false, 2);

            else
                kick(true, 2);
        }

        return true;
    }
    if (ramp)
    {
        if (_x_dir == Direction::RIGHT)
        {
            if (x() <= 88 * TILE && !upsidedown() && !_bouncing && !kicked()) {
                _x_vel_max = 0;
                schedule("stop_mov", 50, [this]() {_x_dir = Direction::LEFT; _x_vel_max = 0.5; });
                setX(x() - 2);
                return true;
            }
            scripted(true);
            _vel.x = 1;
            _schedulers.erase("willhurt");
            _schedulers.erase("get_back");
            _schedulers.erase("up");
            _schedulers.erase("move");
            _schedulers.erase("change_vel");
            _schedulers.erase("vel-y");
            return true;
        }
        else if (_vel.y != 0 || upsidedown() || kicked())
        {
            setX(x() + 2);
            if (!kicked())
                move_on_board();
        }
        schedule("moveRight", 3, [this]() {_x_dir = Direction::RIGHT; });
    }
    return false;
}

void SpearHead::advance() {
    Enemy::advance();
    if (upsidedown() && !_bouncing)
        _x_vel_max = 0;
    if (distX(Game::instance()->wario()) > 9 * TILE && _wario_hit &&
        std::abs(Game::instance()->wario()->x() - _spawn_point.x()) > 9 * TILE && !_dead)
    {
        setPos(_spawn_point);
        _start = true;
        _gliding = false;
        _temp = false;
        _smashed = false;
        _kicked = false;
        _awakening = false;
        _upsidedown = false;
        _dead = false;
        _x_vel_max = 0.5;
        move(_moving_spearhead);
    }
}

QPainterPath SpearHead::shape() const
{
    QPainterPath path;
    path.addRect(10, 1, 13, 14);
    return path;
}
