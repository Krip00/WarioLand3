#include "Spawnable.h"
#include "Sprites.h"
#include "Wario.h"
#include "Sounds.h"
#include "LittleCoin.h"

using namespace WL3;

Spawnable::Spawnable(QPointF pos) : DynamicObject(pos) { }

void Spawnable::spawn()
{
	_y_gravity = 0;
	_vel.y = -0.5;
	_collidable = false;
}

bool Spawnable::hit(Object* what, Direction fromDir)
{
	StaticObject* stc_obj = what->to<StaticObject*>();
	DynamicObject* dyn_obj = what->to<DynamicObject*>();
	if ((stc_obj || (dyn_obj && !dyn_obj->isCompenetrable())) &&
		(fromDir == Direction::LEFT || fromDir == Direction::RIGHT))
	{
		move(inverse(_x_dir));
		return true;
	}

	return false;
}

Spawnable* Spawnable::instance(Type t, QPointF pos)
{
	if (t == Spawnable::Type::COIN || t == Spawnable::Type::MULTICOIN)
		return new LittleCoin(pos);
	else
		return nullptr;
}
