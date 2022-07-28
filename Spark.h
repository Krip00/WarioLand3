#pragma once

#include "Enemy.h"

namespace WL3
{
    class Spark;
}

class WL3::Spark : public Enemy
{

protected:
    bool _check_spawn;
    bool _hit;
    QPixmap _spark[4];
    QPixmap _vanish[3];
 
public:
    
    Spark(QPointF pos, Direction movingDir);
    
    void stop_spark();
    virtual bool hit(Object* what, Direction fromDir) override;
    virtual bool animate() override;
    virtual std::string name() override { return "Spark"; }
    virtual void advance() override;

    QPainterPath shape() const override;
};
