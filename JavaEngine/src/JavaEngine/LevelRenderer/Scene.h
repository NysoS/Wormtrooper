#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Events/Event.h"

namespace JavaEngine
{
	class JE_API Scene
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void OnUpate();
		virtual void OnRenderer();
		virtual void OnEvent(Event& event);

	protected:
		std::string m_Name;
	};
}
