#include "Application.h"

#include "Log.h"
#include "JavaEngine/Events/ApplicationEvent.h"

namespace JavaEngine
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent resizeEvent(1100, 600);
		if(resizeEvent.IsInCategory(EventCategoryApplication))
		{
			JE_TRACE(resizeEvent);
		}
		if(resizeEvent.IsInCategory(EventCategoryInput))
		{
			JE_TRACE(resizeEvent);
		}
		
		while (true)
		{
		}
	}
}
