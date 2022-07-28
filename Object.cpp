#include "Object.h"
#include "Game.h"

using namespace WL3;

static int created = 0;

Object::Object(QPointF pos)
{
	_id = created++;
	_collidable = true;
	_compenetrable = false;
	_freezed = true;
	_collider_visible = false;
	_collider_color = Qt::red;
	_animation_counter = 0;
	setZValue(1);


    // le collisioni si basano sul rettangolo
	setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

	setCacheMode(QGraphicsItem::DeviceCoordinateCache);

	Game::instance()->world()->addItem(this);

	setPos(pos);
}

void Object::schedule(const std::string& id, int delay, std::function<void()> action)
{
	_schedulers[id] = Scheduler(delay, action);
}

void Object::updateSchedulers()
{
	for (auto& t : _schedulers)
		if (t.second.on())
			t.second++;
}

void Object::toggleCollider()
{
	if (_collidable)
	{

		if (!_collider_visible)
		{
			_collider_visible = true;
			(new QGraphicsRectItem(collider(), this))->setPen(QPen(QBrush(_collider_color), 1));
		}
		else
		{
			_collider_visible = false;
			for (auto& i : childItems())
				delete i;
			childItems().clear();
		}
	}
}

void Object::unfreezeWhenVisible()
{
	if (_freezed)
	{
		if (x() <= Game::instance()->sceneRect().right())
			_freezed = false;
	}
}
