#pragma once
#include "Enemy.h"

namespace WL3
{
    class Fireball;
}

class WL3::Fireball : public Enemy
{
protected:
    QPixmap _fireball[4];
    QPixmap _vanish[2];
public:
    
    Fireball(QPointF pos, Direction movingDir, double vely=0.02);
    
    // overrides
    virtual bool hit(Object* what, Direction fromDir) override;
    virtual bool animate() override;
    virtual std::string name() override { return "Fireball"; }
    
    // collider override
    QPainterPath shape() const override;
};
