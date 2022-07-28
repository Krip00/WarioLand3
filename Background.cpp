#include "Background.h"
#include "Sprites.h"
using namespace WL3;

Background::Background(QPointF pos, std::string _texture_path) : Object(pos)
{
    // gli oggetti in background non si possono colpire
	_collidable = false;
	_compenetrable = true;

    // carica le texture
	setPixmap(Sprites::loadTexture(_texture_path, Qt::magenta));

    setPos(pos - QPoint(0, pixmap().height()));
}
