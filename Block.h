#pragma once
#include "DynamicPlatform.h"
#include "Spawnable.h"

namespace WL3 {	class Block; }

class WL3::Block : public DynamicPlatform
{
public:
	enum class Type { BRICK, WALL, HIDDEN, TELEPORTIN, TELEPORTOUT, FIRE, LADDERUP };

protected:
	QPointF _teleport;
	QPointF _pos;
	Block::Type _type;
	Spawnable::Type _spawnable;
	bool _bouncing;
	bool _disabled;
	bool _middle_ladder;
	bool _crouch;

public:

	Block(
		QPointF pos, QPixmap texture,
		Block::Type type = Block::Type::BRICK,
		Spawnable::Type spawnable = Spawnable::Type::NONE,
		int zValue = 40, QPointF teleport = QPoint(0, 0), bool middle_ladder = false);

	Block(
		QPointF pos,
		Block::Type type = Block::Type::BRICK,
		Spawnable::Type spawnable = Spawnable::Type::NONE, bool crouch = false);

	QPointF teleport() { return _teleport; }
	Type type() { return _type; }
	bool middle_ladder() { return _middle_ladder; };

    // Metodi astratti
    virtual bool animate() override { return false; };
	virtual bool hit(Object* what, Direction fromDir) override;
	virtual std::string name() override { return "Block"; }

    // Azioni
	virtual void bounce();
	virtual void smash();
	virtual void disable() { _disabled = true; }

    // funzione che crea un muro di blocchi
	static void createWall(int x, int y, int w, int h);
};
