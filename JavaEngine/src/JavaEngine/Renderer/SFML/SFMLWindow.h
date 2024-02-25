#pragma once

#include "JavaEngine/Core/Window.h"
#include <SFML/Graphics.hpp>

namespace JavaEngine
{
	class SFMLWindow : public Window
	{
	public:
		SFMLWindow(const WindowProps& props);
		virtual ~SFMLWindow();

		void OnUpdate(const float& deltaTime) override;
		void OnRenderer() override;
		void HandleEvent() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallack = callback; }
		inline void SetUpdateCallback(const EventUpdateCallbackFn& callback) override { m_Data.EventUpdateCallback = callback; }
		inline void SetEventRenderCallback(const EventRenderCallbackFn& callback) override { m_Data.EventRenderCallback = callback; }

		void SetVSync(bool enable) override;
		bool IsVSync() const override;

		float getElapsedTime() override;

		void Draw(const sf::Drawable&) override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		sf::RenderWindow* m_Window;
		sf::Clock m_DeltaClock;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			
			EventCallbackFn EventCallack;
			EventUpdateCallbackFn EventUpdateCallback;
			EventRenderCallbackFn EventRenderCallback;
		};

		WindowData m_Data;
	};
}