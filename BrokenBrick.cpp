#include "BrokenBrick.h"
#include "Sprites.h"
using namespace WL3;

BrokenBrick::BrokenBrick(QPointF pos, double y_vel, double x_vel) : DynamicObject(pos)
{
	_collidable = false;
	_y_gravity = 0.2;
	_vel.x = x_vel;
	if (x_vel > 0)
		_x_dir = Direction::RIGHT;
	else
		_x_dir = Direction::LEFT;
	_vel.y = y_vel;
	_x_dec_rel = 0;
	setZValue(3);

	_texture = Sprites::instance()->get("brokenbrick");
	setPixmap(_texture);
	schedule("destroy_animation", 60, [this]() {setVisible(false); });
}
