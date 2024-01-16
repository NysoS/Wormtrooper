#pragma once

#include <SFML/System/Clock.hpp>

#include "JavaEngine/Layer.h"
#include "JavaEngine/Events/ApplicationEvent.h"
#include "JavaEngine/Events/KeyEvent.h"
#include "JavaEngine/Events/MouseEvent.h"

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
