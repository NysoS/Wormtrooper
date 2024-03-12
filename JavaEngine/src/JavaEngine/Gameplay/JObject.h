#pragma once

#include "jepch.h"
#include "JObject.h"

#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Physics/ColliderIntersect.h"
#include "JavaEngine/Physics/JWorld.h"

class JObjectComponent;

namespace JavaEngine
{
	class JE_API JObject
	{
	public:
		explicit JObject(JPhysics::JWorld* world);
		virtual ~JObject();

		virtual void Update();
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
		JObjectComponent* AddObjectComponent(Component* component)
		{
			if (!std::is_base_of<JObjectComponent, Component>())
			{
				return nullptr;
			}

			if(!component)
			{
				return nullptr;
			}

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

		template<typename Component>
		Component* GetObjectComponent(const std::string& componentName)
		{
			if (!std::is_base_of<JObjectComponent, Component>())
			{
				return nullptr;
			}

			for(auto comp : m_ObjectComponents)
			{
				if(comp->GetName() == componentName)
				{
					return reinterpret_cast<Component*>(comp);
				}
			}

			return nullptr;
		}

		inline bool IsTickableObject() const { return m_IsTickableObject; }

	public:
		//Move to protected after ECS added
		std::string m_Name;
		std::vector<JObjectComponent*> m_ObjectComponents;

		JPhysics::JWorld* getWorld() const;

	protected:
		JPhysics::JWorld* m_world;
		bool m_IsTickableObject = true;
	};
}
