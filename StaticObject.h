#pragma once

#include <QPixmap>
#include "Object.h"

namespace WL3
{
	class StaticObject;
}

class WL3::StaticObject : public Object
{
	public:

        StaticObject(QPointF pos);
        StaticObject(QPointF pos, QColor color, double w, double h);
        StaticObject(QPointF pos, QPixmap texture, double w, double h);
        StaticObject(QPointF pos, QPixmap texture);

		virtual void advance() override {}
		virtual bool animate() override;
        virtual bool hit(Object* what, Direction fromDir) override { return false; }
		virtual std::string name() override { return "StaticObject"; }
};
