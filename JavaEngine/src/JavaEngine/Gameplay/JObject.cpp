#include "JObject.h"

#include "JavaEngine/Core/Log.h"

namespace JavaEngine
{
	JObject::JObject()
	{
	}

	JObject::~JObject()
	{
	}

	void JObject::Renderer()
	{
		JE_INFO("JObject : {0} renderer", m_Name);
	}

}
