#pragma once

#include "jepch.h"

#include "JavaEngine/Core/Core.h"

namespace JavaEngine
{
	class JE_API JObject
	{
	public:
		JObject();
		virtual ~JObject();

		virtual void Update(); //TO Remove
		virtual void Renderer(); //To Remove

	public:
		std::string m_Name;
	};
}
