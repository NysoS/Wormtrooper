#include <JavaEngine.h>

#include "JavaEngine/ImguiTest.h"

class ExampleLayer : public JavaEngine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		imguiTest = new JavaEngine::ImguiTest();
	}

	void OnUpdate() override
	{
		JE_INFO("ExampleLayer::Update");
		imguiTest->Draw();
	}

	void OnEvent(JavaEngine::Event& event) override
	{
		JE_TRACE("Layer {0}", event);
	}
private:
	JavaEngine::ImguiTest* imguiTest;

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