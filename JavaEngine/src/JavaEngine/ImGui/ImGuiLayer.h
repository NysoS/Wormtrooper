#pragma once

#include "JavaEngine/Core/Layer.h"
#include "JavaEngine/Events/ApplicationEvent.h"

namespace JavaEngine
{
	class JE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnRederer() override;
		void OnEvent(Event& event) override;
	};
}
