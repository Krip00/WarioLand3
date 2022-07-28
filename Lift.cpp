#include "Lift.h"
#include "Sprites.h"
#include "Game.h"
#include <QPainter>

using namespace WL3;



Lift::Lift(QPointF pos, bool vertical, bool orizontal, int w, int range,
	QPixmap texture,bool ladderdown, bool reset) : DynamicPlatform(pos)
{
	_compenetrable = false;
	_vertical = vertical;
	_orizontal = orizontal;
	_ladder_down = ladderdown;
	_reset_ph = reset;

	if (_vertical || _orizontal)
	{
		_r0 = (_vertical ? pos.y() : pos.x()) - TILE * range / 2;
		_r1 = (_vertical ? pos.y() : pos.x()) + TILE * range / 2;
	}
	else {
		_r0 = pos.y();
		_r1 = pos.y();
	}

    // sprites composte
	QPixmap collage(w * 8, 8);
	QPainter painter(&collage);
	for (int x = 0; x < w * 16; x += 16)
		painter.drawPixmap(x, 0, texture);
	painter.end();
	collage.setMask(collage.createMaskFromColor(QColor(147, 187, 236)));
	setPixmap(collage);

	if (_vertical)
	{
		_y_gravity = 0.05;
		_y_vel_max = 1;
	}
	else if (_orizontal)
	{
		_y_gravity = 0;
		_x_acc = 0.05;
		_x_dec_skd = 0.05;
		_x_vel_max = 1;
		move(Direction::RIGHT);
	}

}

void Lift::advance()
{
	if (_vertical)
	{
		if (y() < _r0)
			_y_gravity = 0.05;
		else if (y() > _r1)
			_y_gravity = -0.05;
	}
	else if (_orizontal)
	{
		if (x() < _r0)
			move(Direction::RIGHT);
		else if (x() > _r1)
			move(Direction::LEFT);
	}
	else
		_y_gravity = 0;

	DynamicPlatform::advance();
}


bool Lift::hit(Object* what, Direction fromDir)
{
	DynamicPlatform::hit(what, fromDir);

	Wario* wario = what->to<Wario*>();
	if (wario && wario->is_on_pre_fire())
	{
		if (wario->x_vel_last_nonzero() < 0)
			wario->velAdd(Vec2Df(-0.5, 0));
		else
			wario->velAdd(Vec2Df(0.5, 0));
	}
    if (wario && (fromDir == Direction::DOWN || fromDir == Direction::RIGHT || fromDir == Direction::LEFT))
    {
        _compenetrable = true;
		schedule("compenetrable", 2, [this]() {_compenetrable = false; });

		if (fromDir == Direction::DOWN)
			wario->velAdd(Vec2Df(0, -1.3));
		if (_reset_ph && wario->scripted_ladder()) {
			wario->resetPhysics();
			wario->scripted_ladder(false);
		}

	}

	//scala
    else if (wario && fromDir == Direction::UP && _ladder_down && wario->crouch())
    {
		_compenetrable = true;
		schedule("compenetrable", 5, [this]() {_compenetrable = false; });
		wario->setX(x() - 8);
		wario->scripted_ladder(true);
	}

	return true;
}
