#include "Scene.h"

#include "JavaEngine/Core/Log.h"


namespace JavaEngine
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::OnUpate()
	{
		JE_INFO("Scene Update");
	}

	void Scene::OnRenderer()
	{
		JE_INFO("Scene Renderer");
	}

	void Scene::OnEvent(Event& event)
	{
		JE_TRACE("Scene event {0}", event.ToString());
	}
}
