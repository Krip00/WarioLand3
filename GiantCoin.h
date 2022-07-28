#pragma once

#include "Spawnable.h"

namespace WL3
{
    class GiantCoin;
}

class WL3::GiantCoin : public Spawnable
{
	protected:

        QPixmap _texture[12];
	public:
        GiantCoin(QPointF pos, int z = 999);

		virtual bool animate() override;
        virtual bool hit(Object* what, Direction fromDir) override;
        virtual std::string name() override { return "GiantCoin"; }
		virtual void spawn() override;
};
