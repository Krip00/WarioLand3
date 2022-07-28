#pragma once
#include "Spawnable.h"

namespace WL3
{
    class Chest;
}

class WL3::Chest : public Spawnable
{
    protected:
        QPixmap _texture[3];
    public:
        Chest(QPointF pos, int z = 999);

        virtual bool animate() override;
        virtual bool hit(Object* what, Direction fromDir) override {return false;};
        virtual std::string name() override { return "Chest"; }
        virtual void spawn() override;
        QPainterPath shape() const override; // collider override
};
