#include "jepch.h"

#include "SFMLWindow.h"

#include <imgui-SFML.h>
#include <imgui.h>

#include "JavaEngine/Core/Log.h"
#include "JavaEngine/Events/ApplicationEvent.h"
#include "JavaEngine/Events/KeyEvent.h"
#include "JavaEngine/Events/MouseButton.h"
#include "JavaEngine/Events/MouseEvent.h"

namespace JavaEngine
{
	static bool s_SFMLInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new SFMLWindow(props);
	}

	SFMLWindow::SFMLWindow(const WindowProps& props)
	{
		Init(props);
	}

	SFMLWindow::~SFMLWindow()
	{
		Shutdown();
	}

	void SFMLWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		JE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		m_Window = new sf::RenderWindow(sf::VideoMode(m_Data.Width, m_Data.Height), m_Data.Title);

		SetVSync(true);

		//ImGui::SFML::Init(*m_Window);
		m_DeltaClock = sf::Clock();
	}

	void SFMLWindow::Shutdown()
	{
		m_Window->close();
	}

	void SFMLWindow::OnUpdate(const float& deltaTime)
	{
		m_Data.EventUpdateCallback(deltaTime);
		//ImGui::ShowDemoWindow();
		//ImGui::SFML::Update(*m_Window, m_DeltaClock.getElapsedTime());
	}

	void SFMLWindow::OnRenderer()
	{
		m_Window->clear();

		m_Data.EventRenderCallback();

		m_Window->display();
	}

	void SFMLWindow::HandleEvent()
	{
		sf::Event sfEvent;
		while (m_Window->pollEvent(sfEvent))
		{
			//ImGui::SFML::ProcessEvent(*m_Window, sfEvent);

			if(sfEvent.type == sf::Event::Resized)
			{
				m_Data.Width = sfEvent.size.width;
				m_Data.Height = sfEvent.size.height;

				WindowResizeEvent event(sfEvent.size.width, sfEvent.size.height);
				m_Data.EventCallack(event);
			}

			if(sfEvent.type == sf::Event::Closed)
			{
				WindowCloseEvent event;
				m_Data.EventCallack(event);
			}

			if (sfEvent.type == sf::Event::KeyPressed)
			{
				KeyPressedEvent event(static_cast<KeyCode>(sfEvent.key.scancode), 0);
				m_Data.EventCallack(event);
			}

			if(sfEvent.type == sf::Event::KeyReleased)
			{
				KeyReleasedEvent event(static_cast<KeyCode>(sfEvent.key.scancode));
				m_Data.EventCallack(event);
			}

			if(sfEvent.type == sf::Event::MouseWheelScrolled)
			{
				MouseScrolledEvent event(sfEvent.mouseWheelScroll.x, sfEvent.mouseWheelScroll.y);
				m_Data.EventCallack(event);
			}

			if(sfEvent.type == sf::Event::MouseMoved)
			{
				MouseMovedEvent event(sfEvent.mouseMove.x, sfEvent.mouseMove.y);
				m_Data.EventCallack(event);
			}

			if(sfEvent.type == sf::Event::MouseButtonPressed)
			{
				MouseButtonPressedEvent event(static_cast<MouseButton>(sfEvent.mouseButton.button));
				m_Data.EventCallack(event);
			}

			if(sfEvent.type == sf::Event::MouseButtonReleased)
			{
				MouseButtonReleasedEvent event(static_cast<MouseButton>(sfEvent.mouseButton.button));
				m_Data.EventCallack(event);
			}
		}
	}


	void SFMLWindow::SetVSync(bool enable)
	{
		if (enable)
		{
			m_Window->setVerticalSyncEnabled(true);
		}else
		{
			m_Window->setVerticalSyncEnabled(false);
		}

		m_Data.VSync = enable;
	}

	bool SFMLWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	float SFMLWindow::getElapsedTime()
	{
		return m_DeltaClock.restart().asSeconds();
	}

	void SFMLWindow::Draw(const sf::Drawable& drawable)
	{
		m_Window->draw(drawable);
	}
};
