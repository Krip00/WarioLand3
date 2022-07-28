#pragma once

#include "DynamicObject.h"

namespace WL3
{
	class Spawnable;
}

class WL3::Spawnable : public DynamicObject
{
	public:
        enum class Type { NONE, COIN, MULTICOIN };

		Spawnable(QPointF pos);

		virtual bool animate() override { return false; }
		virtual bool hit(Object* what, Direction fromDir) override;
		virtual std::string name() override = 0;

        // default spawn
		virtual void spawn();

		static Spawnable* instance(Type t, QPointF pos);
};
