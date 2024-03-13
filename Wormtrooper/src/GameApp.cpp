#include <JavaEngine.h>

#include "Game/Scene/MainScene.h"

class GameApp : public JavaEngine::Application
{
public:
	GameApp()
	{
		PushOverlay(new JavaEngine::ImGuiLayer());
		AddScene(new MainScene());
	}

	~GameApp()
	{
		
	}
};

JavaEngine::Application* JavaEngine::CreateApplication()
{
	return new GameApp();
}