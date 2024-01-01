#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

namespace JavaEngine
{
	class JE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}

#endif