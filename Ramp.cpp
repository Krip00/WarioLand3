#include "Ramp.h"
using namespace WL3;

Ramp::Ramp(QPointF pos, double h) : StaticObject(pos, QColor(0, 0, 0), 1, 1)
{
	setZValue(2);
}
