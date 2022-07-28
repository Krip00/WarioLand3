#pragma once

#include "StaticObject.h"

namespace WL3
{
	class Ramp;
}

class WL3::Ramp : public StaticObject
{
public:

	Ramp(QPointF pos, double h);


	virtual bool hit(Object* what, Direction fromDir) override { return true; }
	virtual std::string name() override { return "Ramp"; }
};
