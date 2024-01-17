#include "Scene.h"

#include "JavaEngine/Core/Log.h"

namespace JavaEngine
{
	Scene::Scene()
	{
		//TODO: Remove test
		JObject* tomate = AddObjectToScene<JObject>(new JObject());
		tomate->m_Name = "Tomate";

		//TODO: Remove test
		JObject* pomme = AddObjectToScene<JObject>(new JObject());
		pomme->m_Name = "Pomme";
	}

	Scene::~Scene()
	{
		for(auto* object : m_ObjectList)
		{
			JE_WARN("Delete : {0}", object->m_Name); //TODO: Remove test
			delete object;
		}

		m_ObjectList.clear();
	}

	void Scene::OnUpate()
	{
		//JE_INFO("Scene Update");
		const std::vector<JObject*> objectListCopy = m_ObjectList;
		for(auto* object : objectListCopy)
		{
			object->Update();
		}
	}

	void Scene::OnRenderer()
	{
		//JE_INFO("Scene Renderer");
		const std::vector<JObject*> objectListCopy = m_ObjectList;
		for (auto* object : objectListCopy)
		{
			object->Renderer();
		}
	}

	void Scene::OnEvent(Event& event)
	{
		//JE_TRACE("Scene event {0}", event.ToString()); //TODO: Remove test
	}
}
