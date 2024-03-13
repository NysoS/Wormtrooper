#pragma once
#include "JavaEngine/Gameplay/JActor.h"

class FlatGround : public JavaEngine::JActor
{
public:
	FlatGround(JPhysics::JWorld* world);
	~FlatGround() override;

	void Update() override;
};