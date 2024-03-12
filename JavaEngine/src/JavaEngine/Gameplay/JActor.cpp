#include "JActor.h"

#include "JavaEngine/Core/Log.h"

namespace JavaEngine
{
	JActor::JActor(JPhysics::JWorld* world)
		: JObject(world)
	{
		//TODO: move to game
		JPhysics::RigidBodyf* rigid = JPhysics::RigidBodyf::CreateBoxBody(20.f, 20.f, 10.f, false, 0);
		rigid->MoveTo(JMaths::Vector2Df(400., 400.f));

		if(getWorld())
		{
			getWorld()->AddRigidbody(rigid);
		}
		AddObjectComponent(rigid);
	}

	JActor::~JActor()
	{
		JE_CORE_INFO("Actor Delete");
	}

	void JActor::Update()
	{
		JObject::Update();
		JE_CORE_INFO("Actor {0} Tickable", m_Name);

		JPhysics::RigidBodyf* rig = GetObjectComponent<JPhysics::RigidBodyf>("Rigidbody");
	}

}
