#include "jepch.h"

#include "SFMLWindow.h"
#include "JavaEngine/Log.h"

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

		m_Window = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(m_Data.Width, m_Data.Height)), m_Data.Title);

		SetVSync(true);

		shape.setFillColor(sf::Color::Green);
	}

	void SFMLWindow::Shutdown()
	{
		m_Window->close();
	}

	void SFMLWindow::OnUpdate()
	{
		JE_CORE_INFO("OnUpdate SFML Window!");
	}

	void SFMLWindow::OnRenderer()
	{
		m_Window->clear();
		m_Window->draw(shape);
		m_Window->display();
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
};
