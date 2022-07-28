#pragma once

#include "Enemy.h"

namespace WL3
{
    class Frog;
}

class WL3::Frog : public Enemy
{
private:
    QPixmap _texture[10];
    QPixmap _texture_angry[28];

    bool _wario_on;

public:    
    Frog(QPointF pos, Direction movingDir = Direction::LEFT);
    
    void wario_on(bool m = true) { _wario_on = m; }
    bool is_on() { return _wario_on; }

    virtual bool hit(Object* what, Direction fromDir) override;
    virtual std::string name() override { return "Frog"; }
    virtual bool animate() override;

    QPainterPath shape() const override;
};
