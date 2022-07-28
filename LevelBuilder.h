#pragma once

#include <QString>
#include "Wario.h"
#include "Enemy.h"

namespace WL3
{
	class LevelBuilder;
}

class WL3::LevelBuilder
{
    public:
        Wario* load(const QString& level_name);
};
