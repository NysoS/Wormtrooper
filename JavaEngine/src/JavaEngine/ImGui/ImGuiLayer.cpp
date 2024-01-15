#include "jepch.h"

#include "ImGuiLayer.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include "JavaEngine/Application.h"
#include "JavaEngine/Renderer/SFML/SFMLWindow.h"

namespace JavaEngine
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		Application& application = Application::Get();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Hello, world!");
		ImGui::Button("Look at this pretty button");
		ImGui::End();
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
	}
}
