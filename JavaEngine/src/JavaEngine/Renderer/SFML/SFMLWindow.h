#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include "JavaEngine/Window.h"
#include <SFML/Graphics.hpp>

namespace JavaEngine
{
	class SFMLWindow : public Window
	{
	public:
		SFMLWindow(const WindowProps& props);
		virtual ~SFMLWindow();

		void OnUpdate() override;
		void OnRenderer() override;
		void HandleEvent() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallack = callback; }
		void SetVSync(bool enable) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		sf::RenderWindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallack;
		};

		WindowData m_Data;

		//Test RenderShape
		sf::CircleShape shape = sf::CircleShape(100.f);
	};
}

#endif
