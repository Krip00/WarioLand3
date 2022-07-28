#include "Torch.h"
#include "Sprites.h"
#include "Wario.h"
#include "Fireball.h"

using namespace WL3;

Torch::Torch(QPointF pos, Direction movingDir) : Enemy(pos, movingDir)
{
    // attributi
    _check_spawn1 = false;
    _check_spawn2 = true;
    schedule("fireballgenerator2", 60 * 5, [this]() {_check_spawn2 = false; });


    _collidable = true;
    _compenetrable = true;

    // sprites
    _torch[0] = Sprites::instance()->get("torch-0");
    _torch[1] = Sprites::instance()->get("torch-1");
    _torch[2] = Sprites::instance()->get("torch-2");
    _torch[3] = Sprites::instance()->get("torch-3");

    setPixmap(_torch[0]);
    setY(y() - 16);
}


bool Torch::hit(Object* what, Direction fromDir)
{
    Wario* wario = what->to<Wario*>();

    if (wario && !wario->is_on_pre_fire())
    {
        wario->pre_fire(true);
        return true;
    }

    return false;
}

bool Torch::animate()
{
    _animation_counter++;

    setPixmap(_torch[(_animation_counter / 16) % 4]);

    return true;
}

void Torch::advance()
{
    if (!_check_spawn1)
    {
        _check_spawn1 = true;
        new Fireball(QPoint(x(), y() + 24), Direction::LEFT);
        new Fireball(QPoint(x() + 3, y() + 24), Direction::RIGHT);
        schedule("fireballgenerator1", 60 * 10, [this]() {_check_spawn1 = false; });
    }
    if (!_check_spawn2)
    {
        _check_spawn2 = true;
        new Fireball(QPoint(x(), y() + 24), Direction::LEFT, 0.1);
        new Fireball(QPoint(x() + 3, y() + 24), Direction::RIGHT, 0.1);
        schedule("fireballgenerator2", 60 * 10, [this]() {_check_spawn2 = false; });
    }
}

QPainterPath Torch::shape() const
{
    QPainterPath path;

    path.addRect(2, 17, 16, 15);
    return path;
}
