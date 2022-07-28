#include "Block.h"
#include "Sprites.h"
#include "Wario.h"
#include "Sounds.h"
#include "Enemy.h"
#include "Spawnable.h"
#include "BrokenBrick.h"
#include "Game.h"

using namespace WL3;
Block::Block(QPointF pos, QPixmap texture, Block::Type type, Spawnable::Type spawnable, 
	int zValue, QPointF teleport, bool middle_ladder) : DynamicPlatform(pos)
{
	_crouch = false;
	_bouncing = false;
	_disabled = false;
	_teleport = teleport;
	_pos = pos;
	_type = type;
	_spawnable = spawnable;
	_middle_ladder = middle_ladder;
	if (_type == Type::HIDDEN)
		_compenetrable = true;
	else
		_compenetrable = false;
	setPixmap(texture);
	setZValue(zValue);
	_y_gravity = 0;
}

Block::Block(QPointF pos, Block::Type type, Spawnable::Type spawnable, bool crouch) : DynamicPlatform(pos)
{
	_bouncing = false;
	_disabled = false;
	_middle_ladder = false;
	_crouch = crouch;
	_pos = pos;
	_type = type;
	_spawnable = spawnable;
	setZValue(1);

	if (_type == Type::BRICK)
		setPixmap(Sprites::instance()->get("brick"));
	else if (_type == Type::WALL)
		setPixmap(Sprites::instance()->get("wall"));
	else
	{
		_compenetrable = true;
		setPixmap(Sprites::instance()->get("invisible"));
		setZValue(999);
	}

    // fisica di default
	_y_gravity = 0;
}

bool Block::hit(Object* what, Direction fromDir)
{
	DynamicPlatform::hit(what, fromDir);
	Wario* wario = what->to<Wario*>();

	if (wario && _type == Block::Type::FIRE && wario->is_on_fire())
		setVisible(false);

	if (!_bouncing && wario && (fromDir == Direction::LEFT || fromDir == Direction::RIGHT) && _type != Block::Type::HIDDEN && !wario->is_on_pre_fire())
	{
		if ((wario->is_run() || wario->rool()) && _type == Block::Type::BRICK)
		{
			if (_crouch)
				wario->can_crouch(true);
			bounce();
			Sounds::instance()->play("break");
			schedule("one-frame-bounce", 1, [this]() {smash(); });
		}

		if (wario->is_run() && _type != Block::Type::HIDDEN && _type != Block::Type::TELEPORTIN && _type != Block::Type::TELEPORTOUT)
		{
			wario->stopimpact(true);
            schedule("run-stop", 1, [wario, fromDir]() {wario->powerdown(inverse(fromDir)); });
		}
	}

	else if (_bouncing && _type != Block::Type::HIDDEN)
	{
		for (auto obj : _attached)
		{
			Enemy* enemy = obj.first->to<Enemy*>();
			if (enemy) {
				enemy->temp(false);
				enemy->start(true);
			}

		}
		_attached.clear();
	}

	else if (wario && !wario->is_on_pre_fire() && fromDir == Direction::DOWN && _type != Block::Type::HIDDEN && _type != Block::Type::TELEPORTIN && _type != Block::Type::TELEPORTOUT && wario->is_run())
	{
		wario->stopimpact(true);
		wario->run(false);
	}
	return true;
}

void Block::bounce()
{
	if (_bouncing)
		return;
	_bouncing = true;

    // un singolo spawnable causa la disattivazione immediata del blocco
	if (_spawnable != Spawnable::Type::NONE && _spawnable != Spawnable::Type::MULTICOIN)
		disable();
    // le monete spawnano subito
	if (_spawnable == Spawnable::Type::COIN || _spawnable == Spawnable::Type::MULTICOIN)
		Spawnable::instance(_spawnable, pos());
    // multicoin diventano monete singole dopo la scadenza
	if (_spawnable == Spawnable::Type::MULTICOIN)
		schedule("multicoin", 300, [this]() {_spawnable = Spawnable::Type::COIN; });

    // fisica del rimbalzo
	_y_gravity = 0.2;
	_vel.y = -2;
	schedule("spawn", 19, [this]() {
		_y_gravity = 0;
		_vel.y = 0;
		_bouncing = false;
		setPos(_pos);
		if (_spawnable != Spawnable::Type::NONE &&
			_spawnable != Spawnable::Type::COIN &&
			_spawnable != Spawnable::Type::MULTICOIN)
			Spawnable::instance(_spawnable, pos());
		});
}

void Block::smash()
{
	setVisible(false);
	new BrokenBrick(_pos + QPointF(8, 0), -3, 2);
	new BrokenBrick(_pos + QPointF(0, 0), -3, -2);
}

void Block::createWall(int x, int y, int w, int h)
{
	for (int i = y; i <= y + h; i++)
		for (int j = x; j <= x + w; j++)
			new Block(QPoint(j * TILE, i * TILE), Block::Type::WALL);
}
