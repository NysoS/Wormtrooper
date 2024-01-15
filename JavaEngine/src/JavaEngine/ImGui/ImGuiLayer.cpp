#include "jepch.h"

#include "ImGuiLayer.h"

#include <imgui-SFML.h>

#include "imgui.h"
#include "JavaEngine/Application.h"
#include "JavaEngine/Log.h"
#include "JavaEngine/Renderer/SFML/SFMLWindow.h"

namespace JavaEngine
{
#define BIND_CALLBACK(fn) (std::bind(&fn, this, std::placeholders::_1))

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGui::ShowDemoWindow();
	}

	void ImGuiLayer::OnRederer()
	{
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
	}
}
