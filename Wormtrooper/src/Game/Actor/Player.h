#pragma once
#include "JavaEngine/Gameplay/JActor.h"

class Player : public JavaEngine::JActor
{
public:
	Player(JPhysics::JWorld* world);
	~Player();
	void Update(const float& deltaTime) override;

	float timer = 0.f;
	float fireRate = .5f;
};