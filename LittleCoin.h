#pragma once

#include "Spawnable.h"

namespace WL3
{
    class LittleCoin;
}

class WL3::LittleCoin : public Spawnable
{
	protected:
        bool _flashing;
        QPixmap _texture[6];
	public:
        LittleCoin(QPointF pos, int z = 999);

		virtual bool animate() override;
        virtual bool hit(Object* what, Direction fromDir) override;
        virtual std::string name() override { return "LittleCoin"; }
		virtual void spawn() override;
};
