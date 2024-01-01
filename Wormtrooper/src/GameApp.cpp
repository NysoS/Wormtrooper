#include <JavaEngine.h>

class GameApp : public JavaEngine::Application
{
public:
	GameApp()
	{
		
	}
	~GameApp()
	{
		
	}
};

JavaEngine::Application* JavaEngine::CreateApplication()
{
	return new GameApp();
}