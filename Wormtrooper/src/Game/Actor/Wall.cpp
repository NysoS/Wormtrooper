#include "Wall.h"

Wall::Wall(JPhysics::JWorld* world)
	: JActor(world)
{
	JPhysics::RigidBodyf* rigid = JPhysics::RigidBodyf::CreateBoxBody(50.f, 80.f, 10.f, true, 0);
	rigid->MoveTo(JMaths::Vector2Df(650.f, 450.f));

	if (getWorld())
	{
		getWorld()->AddRigidbody(rigid);
	}
	AddObjectComponent(rigid);
}

Wall::~Wall()
{
}
