#pragma once

#include "Object.h"
#include "StaticObject.h"

namespace WL3
{
	class DynamicObject;
}

class WL3::DynamicObject : public Object
{
	protected:
        // parametri fisici
        double _y_gravity;		// accelerazione gravitazionale
        double _x_acc;			// acc. orizzontale
        double _x_dec_rel;
        double _x_dec_skd;
        double _x_vel_max;		// vel_max orizzontale
        double _x_vel_min;		// vel_min orizzontale
        double _y_vel_max;		// vel_max verticale
        double _y_vel_min;		// vel_min verticale
        double _y_vel_jmp;		// velocità iniziale quando si salta
        double _x_vel_last_nonzero;	// ultima velocità orizzontale

        // attributi
        Direction _x_dir;		// direzione di movimento orizzontale
        Vec2Df _vel;			// velocità attuale
        Vec2Df _prev_vel;		// velocità nel frame precedente

	public:
		DynamicObject(QPointF pos);

		// getters / setters
		Vec2Df vel() { return _vel; }
		void velAdd(Vec2Df amount);
		void velClip(double vx, double vy);
		void velClipX(double v);
		void velClipY(double v);
		void invertDir() { _x_dir = inverse(_x_dir); }
		bool isSkidding();
		bool isInAir() { return _vel.y != 0 || _prev_vel.y != 0; }
		bool isEndingFalling()   const { return _vel.y == 0 && _prev_vel.y > 0; }
		bool isStartingFalling() const { return (_vel.y >= 0 && _prev_vel.y < 0) || (_vel.y > 0 && _prev_vel.y == 0); }
		bool isCompenetrable() { return _compenetrable; }
        double x_vel_last_nonzero(){return _x_vel_last_nonzero;}
		

        // azioni
		virtual void move(Direction dir);
		virtual void jump(bool on = true);

        // fisica di gioco
        virtual void advance() override;
        virtual void resetPhysics();

        // metodi astratti non implementati
		virtual bool animate() override = 0;
		virtual bool hit(Object* what, Direction fromDir) override = 0;
		virtual std::string name() override = 0;

        // risolve le collisioni
		void resolveCollisions(QList<Object*> likely_collisions);
};
