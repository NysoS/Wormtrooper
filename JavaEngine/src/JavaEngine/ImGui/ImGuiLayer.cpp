#include "jepch.h"

#include "ImGuiLayer.h"

#include "imgui.h"
#include "JavaEngine/Core/Application.h"
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
		
	}

	void ImGuiLayer::OnRederer()
	{
		
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
	}
}
