#include "DynamicObject.h"
#include "CollisionUtils.h"
#include "Game.h"
using namespace WL3;

DynamicObject::DynamicObject(QPointF pos) : Object(pos)
{
    // oggetti dinamici si possono compenetrare
	_compenetrable = true;
	resetPhysics();

	_x_dir = Direction::NONE;
	_vel = { 0, 0 };
}
void DynamicObject::resetPhysics()
{
	// default physics
	_y_gravity = 0.4375;
	_y_vel_max = 3.5;
	_y_vel_min = 0.01;
	_y_vel_jmp = 3.5;
	_x_vel_max = 1.5625;
	_x_vel_min = 1.5625;
    _x_acc = 1000;          // infinito = cambia subito velocità
    _x_dec_rel = 1000;		// infinito = si ferma subito
    _x_dec_skd = 1000;		// infinito = si ferma subito
    _x_vel_last_nonzero = 0;
}

void DynamicObject::velClip(double vx, double vy)
{
	_vel.x = std::max(_vel.x, -vx);
	_vel.x = std::min(_vel.x, vx);
	_vel.y = std::max(_vel.y, -vy);
	_vel.y = std::min(_vel.y, vy);
}

void DynamicObject::velClipX(double v)
{
	velClip(v, std::numeric_limits<double>::infinity());
}

void DynamicObject::velClipY(double v)
{
	velClip(std::numeric_limits<double>::infinity(), v);
}

void DynamicObject::velAdd(Vec2Df amount)
{
	_vel += amount;

    // velocità massima
	velClip(_x_vel_max, _y_vel_max);
	if (_x_dir == Direction::NONE)
		_vel.x = 0;

    // velocità minima
	if (std::abs(_vel.y) < _y_vel_min)
		_vel.y = 0;
}

void DynamicObject::move(Direction dir)
{
	_x_dir = dir;
}

void DynamicObject::jump(bool on)
{

	if (on && !isInAir())
		velAdd(Vec2Df(0, -_y_vel_jmp));
}

bool DynamicObject::isSkidding()
{
	return (_x_dir == Direction::RIGHT && _vel.x < 0) ||
		(_x_dir == Direction::LEFT && _vel.x > 0);
}

void DynamicObject::advance()
{


    // velocità di backup
	if (_vel.x != 0)
		_x_vel_last_nonzero = _vel.x;

	_prev_vel.x = _vel.x;
	_prev_vel.y = _vel.y;


    // applica l'accelerazione gravitazionale
	velAdd(Vec2Df(0, _y_gravity));


    // acc e decel orizzontali
	if (_x_dir == Direction::RIGHT && _vel.x >= 0)
		velAdd(Vec2Df(_x_acc, 0));
	else if (_x_dir == Direction::LEFT && _vel.x <= 0)
		velAdd(Vec2Df(-_x_acc, 0));
	else if (_x_dir == Direction::NONE)
		velAdd(Vec2Df(-_vel.versX() * _x_dec_rel, 0));
	else if (isSkidding())
		velAdd(Vec2Df(-_vel.versX() * _x_dec_skd, 0));

    // risolve le collisioni se necessario
	if (_collidable)
	{
        // simula il prossimo frame
		QPointF curPos = pos();
		QRectF curRect = sceneCollider();
		setX(x() + _vel.x);
		setY(y() + _vel.y);
		QList<Object*> objects_in_rect;
		QList<QGraphicsItem*> items_in_rect = Game::instance()->world()->items(sceneCollider().united(curRect));
		for (auto item : items_in_rect)
		{
			Object* obj = dynamic_cast<Object*>(item);
			if (obj && obj->collidable() && obj != this)
				objects_in_rect.push_back(obj);
		}
        setPos(curPos);

		resolveCollisions(objects_in_rect);
	}

	setX(x() + _vel.x);
	setY(y() + _vel.y);
}

void DynamicObject::resolveCollisions(QList<Object*> likely_collisions)
{
	Vec2Df cp, cn;
	double ct = 0, min_t = INFINITY;
	std::vector<std::pair<Object*, double>> sortedByContactTime;
	for (auto& obj : likely_collisions)
		if (DynamicRectVsRect(RectF{ posv(), sizev() }, vel(), RectF{ obj->posv(), obj->sizev() }, cp, cn, ct))
			sortedByContactTime.push_back({ obj, ct });
	std::sort(sortedByContactTime.begin(), sortedByContactTime.end(),
		[this](const std::pair<Object*, double>& a, const std::pair<Object*, double>& b)
		{
			return a.second != b.second ? a.second < b.second : distX(a.first) < distX(b.first);
		});

	for (auto obj : sortedByContactTime)
		if (DynamicRectVsRect(RectF{ posv(), sizev() }, vel(), RectF{ obj.first->posv(), obj.first->sizev() }, cp, cn, ct))
		{
			if (!obj.first->compenetrable())
				velAdd(cn * Vec2Df(std::abs(_vel.x), std::abs(_vel.y)) * (1 - ct));

			obj.first->hit(this, normal2dir(cn));
			hit(obj.first, inverse(normal2dir(cn)));
		}
}

