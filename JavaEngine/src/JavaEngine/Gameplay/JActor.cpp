#include "JActor.h"

#include "JavaEngine/Core/Log.h"

namespace JavaEngine
{
	JActor::JActor()
	{
	}

	JActor::~JActor()
	{
		JE_CORE_INFO("Actor Delete");
	}

	void JActor::Update()
	{
		JObject::Update();
		JE_CORE_INFO("Actor {0} Tickable", m_Name);
	}

}