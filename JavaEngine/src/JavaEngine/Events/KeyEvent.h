#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include "Event.h"
#include <sstream>

namespace JavaEngine
{
	class JE_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; };

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keyCode) : m_KeyCode(keyCode)
		{
		}

		int m_KeyCode;
	};

	class JE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount)
		{
		}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream stringstream;
			stringstream << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return stringstream.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class JE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode) : KeyEvent(keyCode)
		{
		}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream stringstream;
			stringstream << "KeyPressedEvent: " << m_KeyCode;
			return stringstream.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}

#endif