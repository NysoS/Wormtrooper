#include "Player.h"

Player::Player(JPhysics::JWorld* world)
	: JActor(world)
{
	JPhysics::RigidBodyf* rigid = JPhysics::RigidBodyf::CreateBoxBody(20.f, 20.f, 10.f, false, 0);

	if (getWorld())
	{
		getWorld()->AddRigidbody(rigid);
	}
	AddObjectComponent(rigid);
}

Player::~Player()
{
}
