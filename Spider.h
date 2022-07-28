#pragma once

#include "Enemy.h"

namespace WL3
{
    class Spider;
}

class WL3::Spider : public Enemy
{

private:
    QPixmap primary_texture[11];
    QPixmap mini_spider[23];
    bool _check_spawn;
	int _spawn_count;

public:
    Spider(QPointF pos, Direction movingDir = Direction::LEFT);
    
    virtual std::string name() override { return "Spider"; }
    virtual bool hit(Object* what, Direction fromDir) override;
    virtual bool animate() override;
    virtual void advance() override;

    QPainterPath shape() const override;
};
