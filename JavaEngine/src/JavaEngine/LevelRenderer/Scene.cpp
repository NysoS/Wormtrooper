#include "Scene.h"

#include "JavaEngine/Core/Log.h"
#include "JavaEngine/Gameplay/JActor.h"

namespace JavaEngine
{
	Scene::Scene()
	{
		//TODO: Remove test
		JObject* tomate = AddObjectToScene<JActor>();
		tomate->m_Name = "Tomate";

		//TODO: Remove test
		JObject* pomme = AddObjectToScene<JActor>();
		pomme->m_Name = "Pomme";
	}

	Scene::~Scene()
	{
		for (auto* object : m_ObjectList)
		{
			delete object;
		}
		m_ObjectList.clear();
	}

	void Scene::OnUpate()
	{
		//JE_INFO("Scene Update");
		for(const auto& object : m_ObjectList)
		{
			if(object->IsTickableObject())
			{
				object->Update();
			}
		}
	}

	void Scene::OnRenderer()
	{
		//JE_INFO("Scene Renderer");
		/*const std::vector<JObject*> objectListCopy = m_ObjectList;
		for (auto* object : objectListCopy)
		{
			object->Renderer();
		}*/
	}

	void Scene::OnEvent(Event& event)
	{
		//JE_TRACE("Scene event {0}", event.ToString()); //TODO: Remove test
	}
}
