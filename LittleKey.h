#pragma once

#include "Key.h"

namespace WL3
{
    class LittleKey;
}

class WL3::LittleKey : public Key
{

    public:
        LittleKey(QPointF pos, Key::Color c);

        virtual bool animate() override;
        virtual bool hit(Object* what, Direction fromDir) override;
        virtual std::string name() override { return "LittleKey"; }
        virtual void spawn() override;
};
