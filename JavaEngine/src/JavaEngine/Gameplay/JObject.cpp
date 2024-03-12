#include "JObject.h"

#include "JavaEngine/Core/Log.h"

namespace JavaEngine
{
	JObject::JObject(JPhysics::JWorld* world)
		: m_world(world)
	{

	}

	JObject::~JObject()
	{
	}

	void JObject::Update()
	{
	}

	void JObject::Renderer()
	{
		JE_INFO("JObject : {0} renderer", m_Name);
	}

	JPhysics::JWorld* JObject::getWorld() const
	{
		return m_world;
	}
}
