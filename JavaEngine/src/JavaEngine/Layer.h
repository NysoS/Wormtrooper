#ifndef LAYER_H
#define LAYER_H

#include "JavaEngine/Core.h"
#include "JavaEngine/Events/Event.h"

namespace JavaEngine
{
	class JE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnRederer() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}

#endif