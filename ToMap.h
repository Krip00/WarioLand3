#pragma once

#include "Spawnable.h"

namespace WL3
{
    class ToMap;
}

class WL3::ToMap : public Spawnable
{
    protected:
        QPixmap _texture[5];
    public:
        ToMap(QPointF pos, int z = 999);

        virtual bool animate() override;
        virtual std::string name() override { return "ToMap"; }
        virtual void spawn() override;
};
