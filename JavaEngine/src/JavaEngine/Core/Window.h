#pragma once

#include "jepch.h"
#include "JavaEngine/Core/Core.h"
#include "JavaEngine/Events/Event.h"

namespace JavaEngine
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Java Engine", unsigned int width = 1280, unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class JE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		using EventRenderCallbackFn = std::function<void()>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual void OnRenderer() = 0;
		virtual void HandleEvent() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetEventRenderCallback(const EventRenderCallbackFn& callback) = 0;
		virtual void SetVSync(bool enable) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}