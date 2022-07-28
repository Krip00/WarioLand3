#pragma once

#include "Spawnable.h"
#include "Sprites.h"

namespace WL3
{
    class MenuNumber;
}

class WL3::MenuNumber : public Spawnable
{
    protected:

        QPixmap _menu_number[12];
        int num;
    public:
        MenuNumber(QPointF pos, int c, int z = 999);

        virtual std::string name() override { return "MenuNumber"; }
        virtual void spawn() override;

        QPixmap get();
};
