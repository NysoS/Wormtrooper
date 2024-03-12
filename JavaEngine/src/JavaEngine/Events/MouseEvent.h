#pragma once

#include "Event.h"
#include "MouseButton.h"

namespace JavaEngine
{
    // Classe représentant un événement de déplacement de la souris
    class JE_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }

        std::string ToString() const override
        {
            return "MouseMovedEvent: " + std::to_string(m_MouseX) + ", " + std::to_string(m_MouseY);
        }

        EVENT_CLASS_TYPE(MouseMoved)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_MouseX, m_MouseY;
    };

    // Classe représentant un événement de défilement de la souris
    class JE_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float offsetX, float offsetY) : m_OffsetX(offsetX), m_OffsetY(offsetY) {}

        inline float GetOffsetX() const { return m_OffsetX; }
        inline float GetOffsetY() const { return m_OffsetY; }

        std::string ToString() const override
        {
            return "MouseScrolledEvent: " + std::to_string(m_OffsetX) + ", " + std::to_string(m_OffsetY);
        }

        EVENT_CLASS_TYPE(MouseScroller)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_OffsetX, m_OffsetY;
    };

    // Classe de base pour les événements de bouton de souris
    class JE_API MouseButtonEvent : public Event
    {
    public:
        explicit MouseButtonEvent(MouseButton button) : m_Button(button) {}

        inline MouseButton GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

    protected:
        MouseButton m_Button;
    };

    // Classe représentant un événement de pression de bouton de souris
    class JE_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        explicit MouseButtonPressedEvent(MouseButton button) : MouseButtonEvent(button) {}

        std::string ToString() const override { return "MouseButtonPressedEvent: " + std::to_string(m_Button); }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    // Classe représentant un événement de relâchement de bouton de souris
    class JE_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        explicit MouseButtonReleasedEvent(MouseButton button) : MouseButtonEvent(button) {}

        std::string ToString() const override { return "MouseButtonReleasedEvent: " + std::to_string(m_Button); }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}
