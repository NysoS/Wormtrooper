#pragma once
#include "JavaEngine/Gameplay/JActor.h"

class Player : public JavaEngine::JActor
{
public:
	Player(JPhysics::JWorld* world);
	~Player();
};