#include <JavaEngine.h>

class ExampleLayer : public JavaEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		JE_INFO("ExampleLayer::Update");
	}

	void OnEvent(JavaEngine::Event& event) override
	{
		JE_TRACE("Layer {0}", event);
	}
};

class GameApp : public JavaEngine::Application
{
public:
	GameApp()
	{
		PushLayer(new ExampleLayer());
	}

	~GameApp()
	{
		
	}
};

JavaEngine::Application* JavaEngine::CreateApplication()
{
	return new GameApp();
}