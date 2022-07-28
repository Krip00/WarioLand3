#include "StaticObject.h"
#include "Game.h"
#include "Wario.h"
#include <QPainter>
#include <QBrush>

using namespace WL3;

StaticObject::StaticObject(QPointF pos) : Object(pos)
{
	_collidable = true;
	_collider_color = Qt::yellow;
}

StaticObject::StaticObject(QPointF pos, QColor color, double w, double h) : StaticObject(pos)
{
	QPixmap texture(w, h);
	QPainter painter(&texture);
	painter.setBrush(QBrush(color));
	painter.setPen(Qt::NoPen);
	painter.drawRect(0, 0, w, h);
	painter.end();
	setPixmap(texture);
}

StaticObject::StaticObject(QPointF pos, QPixmap texture, double w, double h) : StaticObject(pos)
{
	QPixmap collage(texture);
	collage = collage.scaled(w, h);
	QPainter painter(&collage);
	for (int y = 0; y < h; y += texture.height())
		for (int x = 0; x < w; x += texture.width())
			painter.drawPixmap(x, y, texture);
	painter.end();
	setPixmap(collage);
}

StaticObject::StaticObject(QPointF pos, QPixmap texture) : StaticObject(pos)
{
	setPixmap(texture);
}

bool StaticObject::animate()
{
	if (_collider_visible)
		return false;

	return false;
}
