#pragma once

#include "Enemy.h"

namespace WL3
{
    class SpearHead;
}

class WL3::SpearHead : public Enemy
{
    protected:
        QPointF _spawn_point;
        Direction _moving_spearhead;
        bool _wario_hit;
        bool _scripted;

	public:

        SpearHead(QPointF pos, Direction movingDir = Direction::LEFT);

        bool scripted() { return _scripted; }

        virtual std::string name() override { return "SpearHead"; }
        virtual bool hit(Object* what, Direction fromDir) override;
        virtual bool animate() override;
        virtual void advance() override;
        virtual void scripted(bool on) { _scripted = on; }

		// collider override
		QPainterPath shape() const override;
};
