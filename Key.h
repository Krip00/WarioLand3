#pragma once
#include "Spawnable.h"

namespace WL3
{
    class Key;
}

class WL3::Key : public Spawnable
{
    public:
        enum class Color { GREY, GREEN, RED, BLUE };

    protected:
        QPixmap _texture[8];
        Color _c;

    public:
        Key(QPointF pos, Key::Color c, int z = 20);

        virtual bool animate() override;
        virtual bool hit(Object* what, Direction fromDir) override;
        virtual std::string name() override { return "Key"; }
        virtual void spawn() override;

        QPainterPath shape() const override;
};
