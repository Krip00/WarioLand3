#pragma once
#include "DynamicObject.h"

namespace WL3
{
    class BrokenBrick;
}

class WL3::BrokenBrick : public DynamicObject
{
protected:
	QPixmap _texture;

public:
	BrokenBrick(QPointF pos, double y_vel, double x_vel);

	virtual bool animate() override { return true; };
	virtual bool hit(Object* what, Direction fromDir) override { return true; }
	virtual std::string name() override { return "BrokenBrick"; }
};
