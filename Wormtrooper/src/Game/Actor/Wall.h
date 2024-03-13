#pragma once
#include "JavaEngine/Gameplay/JActor.h"

class Wall : public JavaEngine::JActor
{
public:
	Wall(JPhysics::JWorld* world);
	~Wall();
};
