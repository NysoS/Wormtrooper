#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Core/Log.h"
#include "JavaEngine/Events/Event.h"
#include "JavaEngine/Gameplay/JObject.h"

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

		template<typename ObjectType>
		ObjectType* AddObjectToScene()
		{
			if (!std::is_base_of<JObject, ObjectType>())
			{
				return nullptr;
			}

			ObjectType* element = new ObjectType();
			m_ObjectList.push_back(element);

			return element;
		}

		template<typename ObjectType>
		void RemoveObjectToScene(ObjectType* object)
		{
			if (!std::is_base_of<JObject, ObjectType>())
			{
				return;
			}

			if (auto it = std::find(m_ObjectList.begin(), m_ObjectList.end(), object); it != m_ObjectList.end())
			{
				m_ObjectList.erase(it);
				delete object;
			}
		}

	protected:
		std::string m_Name;

		std::vector<JObject*> m_ObjectList;
	};
}