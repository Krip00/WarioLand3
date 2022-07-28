#pragma once

#include "Enemy.h"

namespace WL3
{
    class Torch;
}

class WL3::Torch : public Enemy
{

protected:
    bool _check_spawn1;
    bool _check_spawn2;

    QPixmap _torch[4];

public:
    Torch(QPointF pos, Direction movingDir = Direction::LEFT);

    virtual bool hit(Object* what, Direction fromDir) override;
    virtual std::string name() override { return "Torch"; }
    virtual bool animate() override;
    virtual void advance() override;

    QPainterPath shape() const override;
};
