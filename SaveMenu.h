#pragma once

#include "Spawnable.h"

namespace WL3
{
    class SaveMenu;
}

class WL3::SaveMenu : public Spawnable
{
    protected:
        QPixmap _texture[4];
    public:
        SaveMenu(QPointF pos, int z = 999);

        virtual std::string name() override { return "SaveMenu"; }
        virtual void spawn() override;
        virtual bool animate() override;
};
