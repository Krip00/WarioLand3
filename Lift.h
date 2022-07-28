#pragma once

#include "Sprites.h"
#include "DynamicPlatform.h"

namespace WL3
{
	class Lift;
}

class WL3::Lift : public DynamicPlatform
{
	protected:

        double _r0, _r1;		// range di movimenti in x o y
        bool _vertical;			// movimento verticale
        bool _orizontal;        // movimento orizzontale
		bool _ladder_down;
		bool _reset_ph;

	public:
        Lift(QPointF pos, bool vertical = false, bool orizontal=false, int w = 4, int range = 1, QPixmap texture=Sprites::instance()->get("static-platform"), bool ladderdown = false, bool reset=false);

		virtual void advance() override;
		virtual bool animate() override { return false; };
        virtual bool hit(Object* what, Direction fromDir) override;
        virtual std::string name() override { return "Lift"; }
};
