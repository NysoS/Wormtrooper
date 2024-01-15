#include <JavaEngine.h>

class GameApp : public JavaEngine::Application
{
public:
	GameApp()
	{
		//PushLayer(new ExampleLayer);
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