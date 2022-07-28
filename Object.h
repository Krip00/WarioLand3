#pragma once

#include <QGraphicsPixmapItem>
#include <map>
#include "Vec2D.h"
#include "Direction.h"
#include "Scheduler.h"

namespace WL3
{
	class Object;
}

class WL3::Object : public QGraphicsPixmapItem
{
	protected:

        // attributi
		bool _collidable;
        bool _compenetrable;

        // state flags
        bool _freezed;  // le entità si muovono solo quando sono visibili al giocatore. Più efficiente

        // per il debugging
		int _id;
		bool _collider_visible;
		QColor _collider_color;

        // per le animazioni
		int _animation_counter;

        // per lo scheduling delle azioni
		std::map<std::string, Scheduler> _schedulers;
	
	public:
		Object(QPointF pos);

		// getters / setters
		int id() { return _id; }
		virtual bool collidable() { return _collidable; }
        bool compenetrable() { return _compenetrable; }
        bool freezed() { return _freezed; }
		void compenetrable(bool on) { _compenetrable = on;  }
        void collidable(bool on) { _collidable = on;  }


		virtual QRectF collider() { return shape().boundingRect(); }
		virtual QRectF sceneCollider() { return mapRectToScene(collider()); }
		virtual QPointF posColl() { return QPointF(sceneCollider().x(), sceneCollider().y()); }
		virtual Vec2Df posv() { return Vec2Df(sceneCollider().x(), sceneCollider().y()); }
		virtual Vec2Df sizev() { return Vec2Df(collider().width(), collider().height()); }
		virtual bool isRightTo(Object* obj) { return sceneCollider().center().x() >= obj->sceneCollider().center().x(); }
		virtual double distX(Object* obj) { return std::abs(sceneCollider().center().x() - obj->sceneCollider().center().x()); }
        virtual double distY(Object* obj) { return std::abs(sceneCollider().center().y() - obj->sceneCollider().center().y()); }
        virtual void moveBy(Vec2Df amount) { setPos(pos() + QPointF(amount.x, amount.y)); }


        virtual void advance() = 0; // valuta la prossima posizione
        virtual bool animate() = 0; // valuta la prossima animazione
        virtual bool hit(Object* what, Direction fromDir) = 0; // colpito da un altro oggetto
        virtual void unfreezeWhenVisible(); // elimina il freezing se necessario
        virtual std::string name() = 0; // debugging
        virtual void schedule(const std::string & id, int delay, std::function<void()> action); // scheduling delle azioni
		virtual void updateSchedulers();

        // conversioni
		template <class T>
		T to() { return dynamic_cast<T>(this); }

        // mostra/nasconde collider
		void toggleCollider();
};
