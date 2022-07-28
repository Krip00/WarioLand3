#include "Wario.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Game.h"
#include "Block.h"
#include "Ramp.h"
#include "StaticObject.h"
#include "Chest.h"
#include "Spider.h"
#include "Spark.h"
#include "Worm.h"
#include "SpearHead.h"

using namespace WL3;

Wario::Wario(QPointF pos) : DynamicObject(pos)
{
    // state flags 
    _white_screen = false;
    _rool = false;
    _pre_rool = false;
    _nextstop = false;
    _stopimpact = false;
    _up_steps = false;
    _entrable = false;
    _checksleep = false;
    _scripted_ladder = false;
    _sliding = false;
    _initialcrouch = false;
    _gliding = false;
    _black_fire = false;
    _fire = false;
    _pre_fire = false;
    _sleep = false;
    _run = false;
    _invincible = false;
    _crouch = false;
    _fire_run = false;
    _burn_red = false;
    _burn_black = false;
    _burn_normal = false;
    _thunder = false;
    _post_thunder = false;
    _bouncing = false;
    _worm = false;
    _pre_worm = false;
    _post_worm = false;
    _ladder_run = false;
    _ground_bounce = false;
    _scripted = false;
    _bumped = false;
    _scripted = false;
    _jump_ramp = false;
    _script_animation = false;
    _end_screen = false;
    _lock_keys = false;
    _can_crouch = 0;
    _key = 0;

    // sprites
    Sprites::instance()->getWario("stand-0", _texture_stand[0]);
    Sprites::instance()->getWario("stand-0", _texture_stand[1]);
    Sprites::instance()->getWario("stand-0", _texture_stand[2]);
    Sprites::instance()->getWario("stand-1", _texture_stand[3]);
    Sprites::instance()->getWario("stand-2", _texture_stand[4]);
    Sprites::instance()->getWario("stand-1", _texture_stand[5]);
    Sprites::instance()->getWario("stand-2", _texture_stand[6]);
    Sprites::instance()->getWario("stand-1", _texture_stand[7]);
    Sprites::instance()->getWario("sleep-0", _texture_sleep[0]);
    Sprites::instance()->getWario("sleep-1", _texture_sleep[1]);
    Sprites::instance()->getWario("sleep-2", _texture_sleep[2]);
    Sprites::instance()->getWario("sleep-3", _texture_sleep[3]);
    Sprites::instance()->getWario("roll-0", _texture_roll[0]);
    Sprites::instance()->getWario("roll-1", _texture_roll[1]);
    Sprites::instance()->getWario("roll-2", _texture_roll[2]);
    Sprites::instance()->getWario("roll-3", _texture_roll[3]);
    Sprites::instance()->getWario("roll-4", _texture_roll[4]);
    Sprites::instance()->getWario("roll-5", _texture_roll[5]);
    Sprites::instance()->getWario("roll-6", _texture_roll[6]);
    Sprites::instance()->getWario("roll-7", _texture_roll[7]);
    Sprites::instance()->getWario("pre_roll-0", _texture_pre_roll[0]);
    Sprites::instance()->getWario("pre_roll-1", _texture_pre_roll[1]);
    Sprites::instance()->getWario("pre_roll-2", _texture_pre_roll[2]);
    Sprites::instance()->getWario("pre_roll-3", _texture_pre_roll[3]);
    Sprites::instance()->getWario("pre_roll-4", _texture_pre_roll[4]);
    Sprites::instance()->getWario("pre_roll_noscript-0", _texture_pre_roll_noscript[0]);
    Sprites::instance()->getWario("pre_roll_noscript-1", _texture_pre_roll_noscript[1]);
    Sprites::instance()->getWario("pre_roll_noscript-2", _texture_pre_roll_noscript[2]);
    Sprites::instance()->getWario("pre_roll_noscript-3", _texture_pre_roll_noscript[3]);
    Sprites::instance()->getWario("pre_roll_noscript-4", _texture_pre_roll_noscript[4]);
    Sprites::instance()->getWario("stairs-0", _texture_stairs[0]);
    Sprites::instance()->getWario("stairs-1", _texture_stairs[1]);
    Sprites::instance()->getWario("stairs-2", _texture_stairs[2]);
    Sprites::instance()->getWario("stairs-3", _texture_stairs[3]);
    Sprites::instance()->getWario("stairs-4", _texture_stairs[4]);
    Sprites::instance()->getWario("stairs-5", _texture_stairs[5]);
    Sprites::instance()->getWario("stairs-4", _texture_stairs[6]);
    Sprites::instance()->getWario("stairs-3", _texture_stairs[7]);
    Sprites::instance()->getWario("stairs-2", _texture_stairs[8]);
    Sprites::instance()->getWario("stairs-1", _texture_stairs[9]);
    Sprites::instance()->getWario("stairs-down", _texture_stairs[10]);
    Sprites::instance()->getWario("crouch", _texture_crouch[0]);
    Sprites::instance()->getWario("crouch-walk-0", _texture_crouch_walk[0]);
    Sprites::instance()->getWario("crouch-walk-1", _texture_crouch_walk[1]);
    Sprites::instance()->getWario("walk-0", _texture_walk[0]);
    Sprites::instance()->getWario("walk-1", _texture_walk[1]);
    Sprites::instance()->getWario("walk-2", _texture_walk[2]);
    Sprites::instance()->getWario("walk-3", _texture_walk[3]);
    Sprites::instance()->getWario("skid-0", _texture_skid[0]);
    Sprites::instance()->getWario("skid-1", _texture_skid[1]);
    Sprites::instance()->getWario("skid-2", _texture_skid[2]);
    Sprites::instance()->getWario("skid-3", _texture_skid[3]);
    Sprites::instance()->getWario("skid-4", _texture_skid[4]);
    Sprites::instance()->getWario("run-0", _texture_running[0]);
    Sprites::instance()->getWario("run-1", _texture_running[1]);
    Sprites::instance()->getWario("run-2", _texture_running[2]);
    Sprites::instance()->getWario("run-3", _texture_running[3]);
    Sprites::instance()->getWario("run-4", _texture_running[4]);
    Sprites::instance()->getWario("run-5", _texture_running[5]);
    Sprites::instance()->getWario("run-6", _texture_running[6]);
    Sprites::instance()->getWario("run-7", _texture_running[7]);
    Sprites::instance()->getWario("air", _texture_air[0]);
    Sprites::instance()->getWario("fire-0", _texture_fire_run[0]);
    Sprites::instance()->getWario("fire-1", _texture_fire_run[1]);
    Sprites::instance()->getWario("fire-2", _texture_fire_run[2]);
    Sprites::instance()->getWario("fire-3", _texture_fire_run[3]);
    Sprites::instance()->getWario("fire-4", _texture_fire_run[4]);
    Sprites::instance()->getWario("fire-5", _texture_fire_run[5]);
    Sprites::instance()->getWario("fire-6", _texture_fire_run[6]);
    Sprites::instance()->getWario("fire-7", _texture_fire_run[7]);
    Sprites::instance()->getWario("first_fire-0", _texture_burn_red[0]);
    Sprites::instance()->getWario("first_fire-1", _texture_burn_red[1]);
    Sprites::instance()->getWario("first_fire-2", _texture_burn_red[2]);
    Sprites::instance()->getWario("first_fire-3", _texture_burn_red[3]);
    Sprites::instance()->getWario("second_fire-0", _texture_burn_red[4]);
    Sprites::instance()->getWario("second_fire-1", _texture_burn_red[5]);
    Sprites::instance()->getWario("second_fire-2", _texture_burn_red[6]);
    Sprites::instance()->getWario("second_fire-3", _texture_burn_red[7]);
    Sprites::instance()->getWario("third_fire-0", _texture_burn_red[8]);
    Sprites::instance()->getWario("third_fire-1", _texture_burn_red[9]);
    Sprites::instance()->getWario("third_fire-2", _texture_burn_red[10]);
    Sprites::instance()->getWario("third_fire-3", _texture_burn_red[11]);
    Sprites::instance()->getWario("fourth_fire-0", _texture_burn_red[12]);
    Sprites::instance()->getWario("fourth_fire-1", _texture_burn_red[13]);
    Sprites::instance()->getWario("fourth_fire-2", _texture_burn_red[14]);
    Sprites::instance()->getWario("fourth_fire-3", _texture_burn_red[15]);
    Sprites::instance()->getWario("total_black1-0", _texture_burn_black[0]);
    Sprites::instance()->getWario("total_black1-1", _texture_burn_black[1]);
    Sprites::instance()->getWario("total_black1-2", _texture_burn_black[2]);
    Sprites::instance()->getWario("total_black1-3", _texture_burn_black[3]);
    Sprites::instance()->getWario("total_black1-4", _texture_burn_black[4]);
    Sprites::instance()->getWario("total_black1-5", _texture_burn_black[5]);
    Sprites::instance()->getWario("total_black2-0", _texture_burn_black[6]);
    Sprites::instance()->getWario("total_black2-1", _texture_burn_black[7]);
    Sprites::instance()->getWario("total_black2-2", _texture_burn_black[8]);
    Sprites::instance()->getWario("total_black2-3", _texture_burn_black[9]);
    Sprites::instance()->getWario("total_black2-4", _texture_burn_black[10]);
    Sprites::instance()->getWario("total_black2-5", _texture_burn_black[11]);
    Sprites::instance()->getWario("total_black2-6", _texture_burn_black[12]);
    Sprites::instance()->getWario("electric-0", _texture_electric[0]);
    Sprites::instance()->getWario("electric-1", _texture_electric[1]);
    Sprites::instance()->getWario("electric-2", _texture_electric[2]);
    Sprites::instance()->getWario("electric-3", _texture_electric[3]);
    Sprites::instance()->getWario("electric-4", _texture_electric[4]);
    Sprites::instance()->getWario("electric-5", _texture_electric[5]);
    Sprites::instance()->getWario("electric-6", _texture_electric[6]);
    Sprites::instance()->getWario("electric-7", _texture_electric[7]);
    Sprites::instance()->getWario("electric-8", _texture_electric[8]);
    Sprites::instance()->getWario("electric-9", _texture_electric[9]);
    Sprites::instance()->getWario("electric-10", _texture_electric[10]);
    Sprites::instance()->getWario("electric-11", _texture_electric[11]);
    Sprites::instance()->getWario("electric-12", _texture_electric[12]);
    Sprites::instance()->getWario("bump-0", _texture_bump[0]);
    Sprites::instance()->getWario("bump-1", _texture_bump[1]);
    Sprites::instance()->getWario("bump-2", _texture_bump[2]);
    Sprites::instance()->getWario("bump-3", _texture_bump[3]);
    Sprites::instance()->getWario("bump-4", _texture_bump[4]);
    Sprites::instance()->getWario("bump-5", _texture_bump[5]);
    Sprites::instance()->getWario("bump-6", _texture_bump[6]);
    Sprites::instance()->getWario("bump-7", _texture_bump[7]);
    Sprites::instance()->getWario("pre_worm_roll-0", _texture_pre_worm[0]);
    Sprites::instance()->getWario("pre_worm_roll-1", _texture_pre_worm[1]);
    Sprites::instance()->getWario("pre_worm_roll-2", _texture_pre_worm[2]);
    Sprites::instance()->getWario("pre_worm_roll-3", _texture_pre_worm[3]);
    Sprites::instance()->getWario("pre_worm_roll-4", _texture_pre_worm[4]);
    Sprites::instance()->getWario("worm_roll-0", _texture_worm[0]);
    Sprites::instance()->getWario("worm_roll-1", _texture_worm[1]);
    Sprites::instance()->getWario("worm_roll-2", _texture_worm[2]);
    Sprites::instance()->getWario("worm_roll-3", _texture_worm[3]);
    Sprites::instance()->getWario("post_worm_roll-0", _texture_post_worm[0]);
    Sprites::instance()->getWario("post_worm_roll-1", _texture_post_worm[1]);
    Sprites::instance()->getWario("post_worm_roll-2", _texture_post_worm[2]);
    Sprites::instance()->getWario("post_worm_roll-3", _texture_post_worm[3]);
    Sprites::instance()->getWario("post_worm_roll-4", _texture_post_worm[4]);
    Sprites::instance()->getWario("post_worm_roll-5", _texture_post_worm[5]);
    Sprites::instance()->getWario("post_worm_roll-6", _texture_post_worm[6]);
    Sprites::instance()->getWario("post_worm_roll-7", _texture_post_worm[7]);
    Sprites::instance()->getWario("post_worm_roll-8", _texture_post_worm[8]);
    Sprites::instance()->getWario("post_worm_roll-9", _texture_post_worm[9]);
    Sprites::instance()->getWario("post_worm_roll-10", _texture_post_worm[10]);
    Sprites::instance()->getWario("post_worm_roll-11", _texture_post_worm[11]);
    Sprites::instance()->getWario("post_worm_roll-12", _texture_post_worm[12]);
    Sprites::instance()->getWario("post_worm_roll-13", _texture_post_worm[13]);
    Sprites::instance()->getWario("post_worm_roll-14", _texture_post_worm[14]);
    Sprites::instance()->getWario("post_worm_roll-14", _texture_post_worm[15]);

    setPixmap(_texture_stand[0][0]);
    setZValue(4);

    // contatori
    _coins = 0;
    _total_coins = 0;

    setY(y() + 1);

    // default physics
    resetPhysics();
    stage1();
}

void Wario::advance()
{
    _script_animation = false;
    // resetta la gravità quando non salta più
    if (_vel.y >= 0 && !is_run())
        _y_gravity = 0.4375;
    if(bouncing())
        crouch(false);
    if (scripted_ladder())
    {
        if ((crouch() || up_steps()) && Sounds::instance()->isFinished("climb"))
            Sounds::instance()->play("climb");

        if (crouch() && ladder_run())
            _vel.y = 3;
        else if (crouch())
            _vel.y = 0.8;
        else if (up_steps())
            _vel.y = -0.8;
        else
            _vel.y = 0;
        _y_gravity = 0;
        _x_acc = 0;

    }

    if ((crouch() || is_on_fire()) && !is_run() && !is_on_pre_fire() && !rool() && !pre_rool() &&
        !pre_worm() && !worm() && !post_worm())
        _x_vel_max = 1;

    else if (!is_run() && !is_on_pre_fire() && !rool() && !pre_rool() &&
        !pre_worm() && !worm() && !post_worm())
        _x_vel_max = 1.5625;

    // check
    check_roll();
    check_run();
    check_sleep();
    check_bounce();
    check_fire();
    check_worm();
    check_script();

    if (x() == (115 * TILE - 2) && !is_run() && _x_dir == Direction::RIGHT && _can_crouch > 0 
        &&!is_on_pre_fire() && !is_on_fire() && !worm())
        crouch(true);
    else if (x() <= (117 + 0.5) * TILE && x() >= (115 * TILE - 1) && y() <= TILE && y() >= -TILE)
    {
        run(false);
        crouch(true);
        _y_vel_max = 0;
        schedule("y_gravity", 1, [this]() {_y_gravity = 0.4375; _y_vel_max = 3.5; });
    }



    DynamicObject::advance();

    if (scripted())
    {

        if (_x_dir == Direction::RIGHT)
        {
            _script_animation = true;
            _x_vel_last_nonzero = 0.1;
            if (x() < 91.18 * TILE)
            {
                setX(x() + 2);
                setY(y() + 2);
            }
            else
            {
                setY(-TILE);
                setX(91.7 * TILE);
            }
        }
        else if (_x_dir == Direction::LEFT)
        {
            _script_animation = true;
            _x_vel_last_nonzero = -0.1;
            setY(y() - 1);
            setX(x() - 1);
        }

    }

    if (scripted() && !pre_rool() && !bouncing()) {
        _vel.x = 0;
        _vel.y = 0;
        _x_dir = Direction::NONE;
    }
    if (jump_ramp() && scripted())
        velAdd(Vec2Df(0, -4));

    if (_prev_vel.y == 0 && _vel.y > 0 && !_gliding && is_run())
    {
        setY(y() - 3 * _vel.y);
        _vel.y = -_vel.y;
        _gliding = true;
        schedule("gliding", 3, [this]() {_gliding = false; });
    }
}

bool Wario::animate()
{
    _animation_counter++;

    // setta lo stato di wario
    int state_idx = 0;

    int animation_step_move = 3;


    // animazioni
    if (_post_worm)
        setPixmap(_texture_post_worm[(_animation_counter / 15) % 16][state_idx]);
    else if (_pre_fire)
        setPixmap(_texture_fire_run[(_animation_counter / 8) % 8][state_idx]);
    else if (_fire)
        setPixmap(_texture_burn_red[(_animation_counter / 16) % 16][state_idx]);
    else if (_post_thunder)
        setPixmap(_texture_electric[((_animation_counter / 13) % 8) + 5][state_idx]);
    else if (_thunder)
        setPixmap(_texture_electric[(_animation_counter / 13) % 5][state_idx]);
    else if (_pre_worm)
        setPixmap(_texture_pre_worm[(_animation_counter / 23) % 5][state_idx]);
    else if (_worm)
        setPixmap(_texture_worm[(_animation_counter / 4) % 4][state_idx]);
    else if (_bumped)
        setPixmap(_texture_bump[(_animation_counter / 8) % 8][state_idx]);
    else if (_rool)
        setPixmap(_texture_roll[(_animation_counter) % 8][state_idx]);
    else if (_pre_rool && x() > 91.17 * TILE)
        setPixmap(_texture_pre_roll_noscript[(_animation_counter) % 5][state_idx]);
    else if (_pre_rool)
        setPixmap(_texture_pre_roll[(_animation_counter) % 5][state_idx]);
    else if (_scripted_ladder && _crouch && _ladder_run)
        setPixmap(_texture_stairs[10][state_idx]);
    else if (_scripted_ladder && (_crouch || _up_steps))
        setPixmap(_texture_stairs[(_animation_counter / 5) % 10][state_idx]);
    else if (_scripted_ladder)
        setPixmap(_texture_stairs[3][state_idx]);
    else if (_sliding)
        setPixmap(_texture_crouch[0][state_idx]);
    else if (isSkidding())
        setPixmap(_texture_skid[(_animation_counter / animation_step_move) % 5][state_idx]);
    else if (_run && isInAir())
        setPixmap(_texture_running[2][state_idx]);
    else if (_run && _initialcrouch)
        setPixmap(_texture_running[(_animation_counter / animation_step_move) % 8][state_idx]);
    else if (_crouch && _vel.x != 0 && !isInAir())
        setPixmap(_texture_crouch_walk[(_animation_counter / 15) % 2][state_idx]);
    else if (_crouch)
        setPixmap(_texture_crouch[0][state_idx]);
    else if (_run)
        setPixmap(_texture_running[(_animation_counter / animation_step_move) % 8][state_idx]);
    else if (isInAir())
        setPixmap(_texture_air[0][state_idx]);
    else if (_vel.x != 0 || _script_animation)
        setPixmap(_texture_walk[(_animation_counter / animation_step_move) % 4][state_idx]);
    else if (is_sleep())
        setPixmap(_texture_sleep[(_animation_counter / 50) % 4][state_idx]);
    else
        setPixmap(_texture_stand[(_animation_counter / 50) % 8][state_idx]);


    // x-mirroring
    if (_vel.x < 0 || (_vel.x == 0 && _x_vel_last_nonzero < 0))
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));

    // x-mirroring bouncing
    if (bouncing())
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));


    return true;
}



bool Wario::hit(Object* what, Direction fromDir)
{
    Block* block = what->to<Block*>();
    StaticObject* staticObject = what->to<StaticObject*>();
    Ramp* ramp = what->to<Ramp*>();
    SpearHead* spearHead = what->to<SpearHead*>();
    Spark* spark = what->to<Spark*>();
    Chest* chest = what->to<Chest*>();


    if (chest && up_steps())
    {
        _end_screen = true;
        return true;
    }

    if (staticObject && rool() && (fromDir == Direction::LEFT || fromDir == Direction::RIGHT) && !ramp)
    {
        powerdown(_x_dir);
        rool(false);
    }

    if (staticObject && fromDir == Direction::UP)
    {
        setY(y() + 3);
        _vel.y = 0;
    }


    if (staticObject && is_run() && (fromDir == Direction::LEFT || fromDir == Direction::RIGHT) && !ramp)
        powerdown(fromDir);

    if (block && ((block->type() == Block::Type::TELEPORTIN && is_entrable() 
        && !is_on_pre_fire() && !is_on_fire() && !is_run()) || block->type() == Block::Type::TELEPORTOUT))
    {

        if (_x_dir == Direction::LEFT)
            _vel.x = -0.5;
        else
            _vel.x = 0.5;
        _white_screen = true;
        crouch(false);
        jump(false);
        _vel.y = 0;
        if (block->teleport().x() < 31 * TILE)
            stage1();
        else if (block->teleport().x() < 77 * TILE)
            stage2();
        else if (block->teleport().x() < 124 * TILE)
            stage3();
        else
            stage4();
        setPos(block->teleport());
        _entrable = false;
        return true;
    }

    if (block && block->type() == Block::Type::HIDDEN && up_steps() && block->middle_ladder() 
        && !is_on_fire() && !is_on_pre_fire() && !worm() 
        && fromDir == Direction::DOWN && !is_run() && !bouncing())
    {
        setX(block->x() - 8);

        scripted_ladder(true);
        return true;
    }

    if (block && block->type() == Block::Type::LADDERUP && up_steps() 
        && !is_on_fire() && !is_on_pre_fire() && !worm() && !isInAir() && fromDir == Direction::DOWN)
    {

        setX(block->x() - 8);

        scripted_ladder(true);

        return true;
    }



    else if (block && block->type() == Block::Type::LADDERUP && scripted_ladder()) {
        scripted_ladder(false);
        resetPhysics();
    }

    if (ramp && crouch())
        pre_rool(true);



    if (spearHead && !is_on_pre_fire() && !is_on_fire() && !worm())
    {

        if (fromDir == Direction::UP || fromDir == Direction::DOWN || spearHead->upsidedown())
        {

        }
        else if (_x_vel_last_nonzero * spearHead->x_vel_last_nonzero() > 0)
        {
            _vel.y = 0;
            if (_x_vel_last_nonzero > 0 && x() > spearHead->x())
            {

                _x_dir = Direction::LEFT;
                powerdown(_x_dir, 4);
            }
            else if (_x_vel_last_nonzero < 0 && x() < spearHead->x())
            {

                _x_dir = Direction::RIGHT;
                powerdown(_x_dir, 4);
            }
            else
                powerdown(_x_dir);

        }
        else
        {
            if (_x_vel_last_nonzero > 0)
                _x_dir = Direction::RIGHT;
            else
                _x_dir = Direction::LEFT;
            _vel.y = 0;
            powerdown(_x_dir, 4);
        }


        return true;
    }



    if (spark && !is_on_pre_fire() && !is_on_fire() && !spark->dead() && !thunder() && !bouncing())
    {
        _vel.y = 0;
        thunder(true);
        _animation_counter = 0;

        if (fromDir == Direction::UP || fromDir == Direction::DOWN || fromDir == Direction::RIGHT)
            _x_dir = Direction::RIGHT;
        else
            _x_dir = Direction::LEFT;
        powerdown(_x_dir, 4);
        return true;


    }

    return false;
}


QPainterPath Wario::shape() const
{
    QPainterPath path;

    if (_crouch && !_run && !_pre_fire)
        path.addRect(8, 19, 10, 12);

    else
        path.addRect(8, 9, 10, 22);
    return path;
}

void Wario::move(Direction dir)
{
    if ((_run || _sliding) && dir == Direction::NONE)
    {
        if (_x_vel_last_nonzero < 0)
            dir = Direction::LEFT;
        else
            dir = Direction::RIGHT;
    }
    if (!isSkidding() && !(isInAir() && dir == Direction::NONE))
        DynamicObject::move(dir);
}

void Wario::jump(bool on)
{
    if (on)
    {
        if (!isInAir() || _gliding)
        {
            if (std::abs(_vel.x) <= 2.3123)
            {
                velAdd(Vec2Df(0, -4));
                _y_gravity = 0.1150 * 1.5;
            }
            else
            {
                velAdd(Vec2Df(0, -5));
                _y_gravity = 0.0938 * 1.5;
            }

            if (!scripted_ladder() && !(x() <= (117 + 0.5) * TILE && x() >= (115 * TILE - 1)
                && y() <= TILE && y() >= -TILE) && !is_on_pre_fire() && !is_run())
                        Sounds::instance()->play("jump");
        }
    }
    else
        _y_gravity = 0.4375;
}



void Wario::add_key()
{
    _key++;
    if (_key >= Game::instance()->chest_coin()) // 4 chiavi
        new Chest(QPoint(136 * TILE, -11 * TILE), 2);
}


void Wario::scripted_ladder(bool on)
{
    _scripted_ladder = on;
    run(false);
    _run = false;
    Sounds::instance()->stop("run");
    _vel.x = 0;

}

void Wario::invincible(bool on)
{

    _invincible = on;
    if (on)
        schedule("stop_invincible", 10 * 60, [this]() {invincible(false); });


}

void Wario::entrable(bool on)
{
    _entrable = on;
    if (on)
        schedule("entrable", 3, [this]() {entrable(false); });
}

void Wario::sliding(bool on)
{
    if (!on)
    {
        _x_vel_max = 1.5625;
        _x_vel_min = 1.5625;
        _sliding = false;
    }

    if (isInAir())
        return;

    else if (on) {
        run(!on);
        _sliding = on;
        schedule("slid", 29, [this]() {sliding(false); });
    }

}
void Wario::run(bool on)
{
    if (stopimpact())
    {
        _x_dir = Direction::NONE;
        _vel.x = 0;
        _vel.y = 0;
        _run = false;
        if (!Sounds::instance()->isFinished("run"))
            Sounds::instance()->stop("run");
        return;
    }
    if (isInAir() && ((_x_dir == Direction::LEFT && _vel.x > 0) || (_x_dir == Direction::RIGHT && _vel.x < 0)))
    {
        _nextstop = on;
        _x_vel_max = 1.5625;
        _x_vel_min = 1.5625;
        _run = false;
        if (!Sounds::instance()->isFinished("run"))
            Sounds::instance()->stop("run");

    }

    if (isInAir() && !on)
    {
        _nextstop = true;
        return;
    }

    if (!on)
    {
        if (!Sounds::instance()->isFinished("run"))
            Sounds::instance()->stop("run");
        _nextstop = on;
        _x_vel_max = 1.5625;
        _x_vel_min = 1.5625;
        _run = false;
    }

    if (isInAir())
        return;

    else if (on)
    {
        if (!scripted_ladder() && Sounds::instance()->isFinished("run"))
            Sounds::instance()->play("run", true);
        _run = on;
        _x_vel_min = 2.5625;
        _x_vel_max = 2.5625;
        schedule("run", 28, [this]() {run(false); });
    }
}



void Wario::powerdown(Direction fromDir, double xy)
{

    if (bouncing())
        return;
    bouncing(true);
    _run = false;
    Sounds::instance()->stop("run");
    _bouncecount = xy;
    if (xy == 1.566)
        Sounds::instance()->play("jump");
    xy=1.2;
    _x_vel_max = xy;
    _x_vel_min = xy;
    _lock_keys = true; // blocca i comandi mentre è in aria
    move(inverse(_x_dir));
    schedule("exitBump", 28, [this]() {_bumped = false; });


    // colpito da destra ==> va a sinistra
    if (fromDir == Direction::LEFT)
    {
        _vel.x = -xy;
        if (_vel.y == 0) {
            _vel.y = -2.5;
            ground_bounce(true);
        }
        else if (x() > (117 + 0.5) * TILE && x() < (115 * TILE - 1))
        {

            setY(y() - 1);
            _vel.y = 0.1;
        }
        else
            _vel.y = -1;

    }
    // colpito da sinistra ==> va a destra
    else if (fromDir == Direction::RIGHT)
    {

        _vel.x = xy;
        if (_vel.y == 0) {
            _vel.y = -2.5;
            ground_bounce(true);
        }
        else if (x() > (117 + 0.5) * TILE && x() < (115 * TILE - 1))
        {
            setY(y() - 1);
            _vel.y = 0.1;
        }
        else
            _vel.y = -1;
    }
    if (x() <= (117 + 0.5) * TILE && x() >= (115 * TILE - 1) && _can_crouch > 1)
    {
        _vel.y = 0;
        if (_x_dir == Direction::RIGHT)
            setX(x() - 8);
        else if (_x_dir == Direction::LEFT)
            setX(x() + 8);

    }
}

void Wario::sleep(bool on)
{
    if (on)
        _sleep = on;
    else
    {
        _checksleep = on;
        _sleep = on;
    }
}

void Wario::check_worm() {

    if (worm())
    {
        if (_vel.x < 0)
            _x_dir = Direction::LEFT;
        else if (_vel.x > 0)
            _x_dir = Direction::RIGHT;
        else if (_x_vel_last_nonzero < 0)
            _x_dir = Direction::RIGHT;
        else
            _x_dir = Direction::LEFT;
    }
}

void Wario::check_roll()
{
    if (pre_rool())
    {
        _x_dir = Direction::RIGHT;
        velAdd(Vec2Df(0.3, 0));
    }

    if (pre_rool() && (_x_dir == Direction::LEFT && _vel.x > 0)) {
        _schedulers.erase("roll");
        pre_rool(false);
    }

    if (rool())
    {
        if (Sounds::instance()->isFinished("roll"))
            Sounds::instance()->play("roll");
        _x_dir = Direction::RIGHT;
        _x_vel_min = 2.5;
        _x_vel_max = 2.5;
        crouch(true);
        up_steps(false);
        ladder_run(false);
        entrable(false);
        up_steps(false);
    }
}
void Wario::check_bounce()
{
    if (bouncing() && !ground_bounce() && _vel.y == 0)
    {
        _lock_keys = false;
        bouncing(false);
        move(inverse(_x_dir));
        _vel.y = 0;
        _vel.x = 0;

    }
    else if (bouncing() && _vel.y == 0)
    {
        ground_bounce(false);
        bouncing(false);
        move(inverse(_x_dir));
        _vel.y = 0;
        _vel.x = 0;
        if (_bouncecount - 1 > 1.5)
        {
            powerdown(_x_dir, _bouncecount);
            _bouncecount = _bouncecount - 1;
        }
        else
        {

            if (thunder())
                post_thunder(true);
            else
            {
                resetPhysics();
                _lock_keys = false;
            }
        }
    }

}

void Wario::check_sleep()
{
    if (!isInAir() && _vel.x == 0 && !_crouch && _x_dir == Direction::NONE && !checksleep())
    {
        _checksleep = true;
        schedule("sleep", FPS * 27, [this]() { sleep(true); _animation_counter = 0; });

    }
    else if (checksleep() && is_sleep())
    {
        _checksleep = false;
        _schedulers.erase("sleep");
    }
    else if (isInAir() || _vel.x != 0 || _crouch || _x_dir != Direction::NONE)
    {
        sleep(false);
    }
}

void Wario::check_run()
{
    if (nextstop())
        run(false);

    _stopimpact = false;

    if (is_run() && ((_x_dir == Direction::LEFT && _vel.x > 0) || (_x_dir == Direction::RIGHT && _vel.x < 0)))
    {
        _schedulers.erase("run");
        run(false);
    }
    else if (_run && !_initialcrouch && _crouch)
        sliding(true);
    else if ((_sliding && isInAir()) || (_sliding && ((_x_dir == Direction::LEFT && _vel.x > 0) 
        || (_x_dir == Direction::RIGHT && _vel.x < 0))))
    {
        sliding(false);
        _vel.x = 0;

    }
}

void Wario::check_script()
{
    for (int i = 88 * TILE; i < 92 * TILE; i++) {

        if (x() < i - 6 && x() > i - 11 && y() > (-3 * TILE - 88 * TILE + i - 31))
        {
            scripted(true);
            schedule("Noscrip", 2, [this]() {scripted(false); });
            return;
        }
    }

}

void Wario::check_fire()
{
    if (is_on_pre_fire())
    {
        Sounds::instance()->stop("ost_main");
        Sounds::instance()->stop("walk");

        if (_vel.x < 0)
            _x_dir = Direction::LEFT;
        else if (_vel.x > 0)
            _x_dir = Direction::RIGHT;
        else if (_x_vel_last_nonzero < 0 && (x() >= 92 * TILE + 1 || x() <= 87 * TILE + 1))
            _x_dir = Direction::RIGHT;
        else if (_x_vel_last_nonzero < 0) // rampa
            _x_dir = Direction::LEFT;
        else if (_x_vel_last_nonzero > 0 && (x() >= 92 * TILE + 1 || x() <= 87 * TILE + 1))
            _x_dir = Direction::LEFT;
        else if (_x_vel_last_nonzero > 0) // rampa
            _x_dir = Direction::RIGHT;
    }
    
}

void Wario::pre_rool(bool on)
{
    if (!is_on_pre_fire() && !is_on_fire())
    {
        _pre_rool = on;

        if (on)
        {
            Sounds::instance()->play("sliding");
            _animation_counter = 0;
            schedule("roll", FPS * 0.3, [this]() { rool(true); pre_rool(false); });
        }
    }
}


void Wario::rool(bool on)
{
    _rool = on;

    if (!on && !is_on_pre_fire() && !is_on_fire())
        resetPhysics();
}

void Wario::pre_fire(bool on)
{

    if (on && !invincible())
    {
        Sounds::instance()->play("ost_fire", true);

        _pre_fire = on;
        rool(false);
        _vel.x = 0.1;
        _x_vel_max = 2;
        _x_vel_min = 2;
        if (_x_vel_last_nonzero < 0)
            _x_dir = Direction::LEFT;
        else
            _x_dir = Direction::RIGHT;

        schedule("fire", FPS * 12, [this]() { fire(true); pre_fire(false); });
    }
    else if (!on)
    {
        _pre_fire = on;
        resetPhysics();
    }
}
void Wario::fire(bool on)
{
    _fire = on;

    if (on)
        schedule("stopfire", FPS * 4, [this]() { fire(false); blackFire(true);
    Sounds::instance()->stop("ost_fire"); Sounds::instance()->play("ost_main", true); });
    else
        resetPhysics();


}
void Wario::blackFire(bool on)
{
    _animation_counter = 0;
    _black_fire = on;
    schedule("lock_keys", FPS * 5, [this] { _black_fire = false; });
}

void Wario::worm(bool on) {
    if (on && !invincible())
    {
        _worm = on;
        _animation_counter = 0;
        _x_vel_max = 2;
        _x_vel_min = 2;
        if (_x_vel_last_nonzero > 0 || _x_dir == Direction::RIGHT)
            _x_dir = Direction::LEFT;

        else
            _x_dir = Direction::RIGHT;

        schedule("worm", FPS * 15, [this]() { worm(false); });
    }
    else
    {
        _post_worm = true;
        _x_vel_max = 0;
        _x_vel_min = 0;
        _animation_counter = 0;
        schedule("post_worm", FPS * 4, [this]() { _worm = false; resetPhysics(); _post_worm = false;
        Sounds::instance()->stop("ost_worm"); Sounds::instance()->play("ost_main", true); });

    }
}

void Wario::pre_worm(bool on)
{
    if (on && !invincible())
    {
        Sounds::instance()->stop("ost_main");
        Sounds::instance()->play("ost_worm", true);
        _pre_worm = on;
        _animation_counter = 0;
        scripted_ladder(false);
        _y_gravity = 0.4375;
        _x_acc = 1000;
        _x_vel_max = 0;
        _x_vel_min = 0;
        schedule("worm", FPS, [this]() { worm(true); pre_worm(false); });
    }
    else if (!on)
        _pre_worm = on;

}
void Wario::jump_ramp(bool on)
{
    if (on)
    {
        schedule("stop_jump", 3, [this]() { jump_ramp(false); });
        _jump_ramp = true;
    }
    else
        _jump_ramp = false;
}

void Wario::post_thunder(bool on) {
    _post_thunder = on;
    if (on)
    {
        _animation_counter = 0;
        Sounds::instance()->play("thunder_2");
        schedule("post_thunder", FPS, [this]() { post_thunder(false); });
        _x_dir = (Direction::NONE);
        _x_vel_max = 0;
        _y_vel_max = 0;
    }
    else
    {
        thunder(false);
        resetPhysics();
        _lock_keys = false;
    }
}

void Wario::stage1()
{
    for (auto obj : enemyStage)
        obj->setVisible(false);
    enemyStage.clear();
    enemyStage.push_back(new SpearHead(QPoint(11 * TILE, -2 * TILE), Direction::LEFT)); 
    enemyStage.push_back(new SpearHead(QPoint(22 * TILE, -3 * TILE), Direction::LEFT));
}

void Wario::stage2()
{
    for (auto obj : enemyStage)
        obj->setVisible(false);
    enemyStage.clear();
    enemyStage.push_back(new Spider(QPoint(61.3 * TILE, 12 * TILE), Direction::NONE)); 
    enemyStage.push_back(new Spider(QPoint(52.3 * TILE, 12 * TILE), Direction::NONE));
    enemyStage.push_back(new SpearHead(QPoint(43 * TILE, 14 * TILE), Direction::LEFT));
    enemyStage.push_back(new SpearHead(QPoint(49 * TILE, 24 * TILE), Direction::LEFT));
    enemyStage.push_back(new SpearHead(QPoint(66 * TILE, 16 * TILE), Direction::LEFT));
    enemyStage.push_back(new SpearHead(QPoint(74 * TILE, 8 * TILE), Direction::LEFT));
    enemyStage.push_back(new SpearHead(QPoint(72 * TILE, 2 * TILE), Direction::LEFT));
}

void Wario::stage3()
{
    for (auto obj : enemyStage)
        obj->setVisible(false);
    enemyStage.clear();
    enemyStage.push_back(new SpearHead(QPoint(85 * TILE, -5 * TILE), Direction::RIGHT));  
    enemyStage.push_back(new SpearHead(QPoint(97 * TILE, -2 * TILE), Direction::LEFT));  
    enemyStage.push_back(new SpearHead(QPoint(110 * TILE, -1 * TILE), Direction::LEFT));

}

void Wario::stage4()
{
    for (auto obj : enemyStage)
        obj->setVisible(false);
    enemyStage.clear();
    enemyStage.push_back(new Worm(QPoint(134 * TILE, -1 * TILE), Direction::LEFT)); 
    enemyStage.push_back(new Worm(QPoint(129 * TILE, -5 * TILE), Direction::LEFT)); 
}
