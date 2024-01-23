#include <JavaEngine.h>

class GameApp : public JavaEngine::Application
{
public:
	GameApp()
	{
		PushOverlay(new JavaEngine::ImGuiLayer());
	}

	~GameApp()
	{
		
	}
};

JavaEngine::Application* JavaEngine::CreateApplication()
{
	return new GameApp();
}