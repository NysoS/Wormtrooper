#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "Event.h"

namespace JavaEngine
{
	class JE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y)
		{
		}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream stringstream;
			stringstream << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return stringstream.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	class JE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float offsetX, float offsetY) : m_OffsetX(offsetX), m_OffsetY(offsetY)
		{
		}

		inline float GetOffsetX() const { return m_OffsetX; }
		inline float GetOffsetY() const { return m_OffsetY; }

		std::string ToString() const override
		{
			std::stringstream stringstream;
			stringstream << "MouseScrolledEvent " << m_OffsetX << ", " << m_OffsetY;
			return stringstream.str();
		}

		EVENT_CLASS_TYPE(MouseScroller)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_OffsetX, m_OffsetY;
	};

	class JE_API MouseButtonEvent : public Event
	{
	public:
		MouseMovedEvent(int button) : m_Button(button)
		{
		}

		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	protected:

		int m_Button;
	};

	class JE_API MouseButtonPressedEvent : MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button)
		{
		}

		std::string ToString() const override
		{
			std::stringstream stringstream;
			stringstream << "MouseButtonPressedEvent: " << m_Button;
			return stringstream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class JE_API MouseButtonReleasedEvent : MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button)
		{
		}

		std::string ToString() const override
		{
			std::stringstream stringstream;
			stringstream << "MouseButtonReleasedEvent: " << m_Button;
			return stringstream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}

#endif