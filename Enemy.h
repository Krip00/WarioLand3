#pragma once

#include "DynamicObject.h"

namespace WL3
{
	class Enemy;
}

class WL3::Enemy : public DynamicObject
{
    protected:
		// state flags
        bool _smashed;		
        bool _dead;      
        bool _kicked;	
        bool _upsidedown;   
        bool _awakening;	
        bool _gliding;
        bool _on_lift;
        bool _start;
        bool _temp;
        bool _bouncing;

        // animazioni
        QPixmap _texture_walk[3];
        QPixmap _texture_roll[4];
        QPixmap _texture_attack[3];
        QPixmap _texture_smashed;
        QPixmap _texture_upsidedown[4];

	public:

		Enemy(QPointF pos, Direction movingDir = Direction::LEFT);


        virtual void advance() override; // avanza solo quando è vicino a Wario
        virtual bool animate() override {return false;}; // gestisce le animazioni
        virtual bool hit(Object* what, Direction fromDir) override; // gestisce le hit
        virtual void smash(DynamicObject* what); // smash causato da Wario


        // kick e bounce
        virtual void kick(bool right = true, int force=5);
        virtual void bounce(bool right = true, bool wall=false);
        
        void move_on_board();
        void temp(bool on) { _temp = on; }
        void start(bool on) { _start = on; }
        void kicked(bool on) { _kicked = on; }
        
        bool upsidedown(){return _upsidedown;}
        bool dead(){return _dead;}
        bool kicked() { return _kicked;}


		virtual std::string name() override = 0;
};
