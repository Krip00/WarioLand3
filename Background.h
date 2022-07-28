#pragma once
#include "Object.h"

namespace WL3
{
    class Background;
}

// Oggetti di background
class WL3::Background : public Object
{
public:
	Background(QPointF pos, std::string _texture_path);

    // Metodi astratti
	virtual void advance() override {}
	virtual bool animate() override { return true; }
	virtual bool hit(Object* what, Direction fromDir) override { return false; }
	virtual std::string name() override { return "Background"; }
};
