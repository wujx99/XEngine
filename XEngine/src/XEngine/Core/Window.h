#pragma once

#include <sstream>

#include "XEngine/Core/Base.h"
#include "XEngine/Event/Event.h"

namespace XEg
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "XEngine",
			uint32_t width = 1600,
			uint32_t height = 900)
			:Title(title),Width(width),Height(height)
		{}
	};
	// Interface representing a desktop system based window
	class Window
	{
	public:
		using EventCallBackFn = std::function<void(Event&)>;
		virtual ~Window() {}
		virtual void OnUpdate() = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// window attributes
		virtual void SetEventCallBack(const EventCallBackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());


	};
}
