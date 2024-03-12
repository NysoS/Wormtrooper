#pragma once

#include "Event.h"
#include "KeyCode.h"

namespace JavaEngine
{
    class JE_API KeyEvent : public Event
    {
    public:
        inline KeyCode GetKeyCode() const { return m_KeyCode; };

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(const KeyCode keyCode) : m_KeyCode(keyCode)
        {
        }

        KeyCode m_KeyCode;
    };

    class JE_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(const KeyCode keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount)
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
        KeyReleasedEvent(const KeyCode keyCode) : KeyEvent(keyCode)
        {
        }

        std::string ToString() const override
        {
            std::stringstream stringstream;
            stringstream << "KeyPressedEvent: " << m_KeyCode;
            return stringstream.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}
