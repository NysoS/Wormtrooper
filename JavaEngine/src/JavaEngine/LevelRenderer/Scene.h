#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"
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

		//TODO: Move to hxx file
		template<typename ObjectType>
		ObjectType* AddObjectToScene(ObjectType* object)
		{
			if(!dynamic_cast<ObjectType*>(object))
			{
				return nullptr;
			}

			m_ObjectList.push_back(object);

			return object;
		}

		//TODO: Move to hxx file
		template<typename ObjectType>
		void RemoveObjectToScene(ObjectType* object)
		{
			if(!dynamic_cast<ObjectType*>(object))
			{
				return;
			}

			m_ObjectList.erase(std::find(m_ObjectList.begin(), m_ObjectList.end(), object));
		}

	protected:
		std::string m_Name;

		std::vector<JObject*> m_ObjectList;
	};
}
