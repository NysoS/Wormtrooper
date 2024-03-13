#pragma once
#include "JavaEngine/Gameplay/JActor.h"

class Player2 : public JavaEngine::JActor
{
public:
	Player2(JPhysics::JWorld* world);
	~Player2();
	void Update(const float& deltaTime) override;

	float timer = 0.f;
	float fireRate = .5f;
};