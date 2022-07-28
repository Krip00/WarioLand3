#include "DynamicPlatform.h"
#include "Sprites.h"
#include "Game.h"
using namespace WL3;

DynamicPlatform::DynamicPlatform(QPointF pos) : DynamicObject(pos)
{
	_compenetrable = false;
}

void DynamicPlatform::advance()
{
	DynamicObject::advance();

	for (auto obj : _attached)
	{
        // gli oggetti si muovono lungo la piattaforma
		if (obj.second == Direction::UP)
			obj.first->moveBy(_vel);

        // l'oggetto colpisce la piattaforma dal basso -> la posizione dell'oggetto è stata corretta lungo y
		else if (obj.second == Direction::DOWN)
			obj.first->moveBy(Vec2Df(0, _vel.y));

        // l'oggetto colpisce la piattaforma da un lato -> pos dell'oggetto corretto lungo x
		else
			obj.first->moveBy(Vec2Df(_vel.x, 0));
	}
	_attached.clear();
}

bool DynamicPlatform::hit(Object* what, Direction fromDir)
{
	DynamicObject* dyn = what->to<DynamicObject*>();

	if (!_compenetrable && dyn && dyn->isCompenetrable())
		_attached[dyn] = fromDir;

	return false;
}
