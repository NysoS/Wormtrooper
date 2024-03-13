#include "FlatGround.h"

FlatGround::FlatGround(JPhysics::JWorld* world)
	: JActor(world)
{
	JPhysics::RigidBodyf* rigid = JPhysics::RigidBodyf::CreateBoxBody(1000.f, 20.f, 10.f, true, 0);
	rigid->MoveTo(JMaths::Vector2Df(640.f, 500.f));

	if (getWorld())
	{
		getWorld()->AddRigidbody(rigid);
	}
	AddObjectComponent(rigid);
}

FlatGround::~FlatGround()
{
}

void FlatGround::Update(const float& deltaTime)
{
	JActor::Update(deltaTime);
}
