#pragma once

#include "Enemy.h"

namespace WL3
{
    class Worm;
}

class WL3::Worm : public Enemy
{
protected:
    bool _attack;
    bool _check_attack;

public:

    Worm(QPointF pos, Direction movingDir = Direction::LEFT);

    virtual bool hit(Object* what, Direction fromDir) override;
    virtual std::string name() override { return "Worm"; }
    virtual bool animate() override;
    virtual void advance() override;

    QPainterPath shape() const override;
};
