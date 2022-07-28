#pragma once

#include "Spawnable.h"

namespace WL3
{
    class ReturnMenu;
}

class WL3::ReturnMenu : public Spawnable
{
    protected:
        QPixmap _texture[6];
    public:
        ReturnMenu(QPointF pos, int z = 999);

        virtual bool animate() override;
        virtual std::string name() override { return "ReturnMenu"; }
        virtual void spawn() override;
};
