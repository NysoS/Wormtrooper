#pragma once

#include "jepch.h"
#include "JObject.h"

#include "JavaEngine/Core/Core.h"

class JObjectComponent;

namespace JavaEngine
{
	class JE_API JObject
	{
	public:
		JObject();
		virtual ~JObject();

		virtual void Update() {};
		virtual void Renderer(); //Move to renderer component

		template<typename Component>
		JObjectComponent* CreateObjectComponent()
		{
			if(!std::is_base_of<JObjectComponent, Component>())
			{
				return nullptr;
			}

			Component* component = new Component();
			m_ObjectComponents.push_back(component);

			return component;
		}

		template<typename Component>
		void RemoveObjectComponent(Component* component)
		{
			if (!std::is_base_of<JObjectComponent, Component>())
			{
				return;
			}

			m_ObjectComponents.erase(std::find(m_ObjectComponents.begin(), m_ObjectComponents.end(), component));
			delete component;
		}

		inline bool IsTickableObject() const { return m_IsTickableObject; }

	public:
		//Move to protected after ECS added
		std::string m_Name;
		std::vector<JObjectComponent*> m_ObjectComponents;

	protected:
		bool m_IsTickableObject = true;
	};
}
