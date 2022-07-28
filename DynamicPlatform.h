#pragma once

#include "DynamicObject.h"
#include <map>

namespace WL3
{
	class DynamicPlatform;
}

class WL3::DynamicPlatform : public DynamicObject
{
	protected:

		std::map<DynamicObject*, Direction> _attached;

	public:

		DynamicPlatform(QPointF pos);

		virtual void advance() override;
		virtual bool hit(Object* what, Direction fromDir) override;

        // non implementati
        virtual bool animate() override = 0;
        virtual std::string name() override = 0;
};
