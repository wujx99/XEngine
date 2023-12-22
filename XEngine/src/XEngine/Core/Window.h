#pragma once

#include "xepch.h"

#include "XEngine/Core/Core.h"
#include "XEngine/Event/Event.h"

namespace XEg
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "XEngine",
			unsigned int width = 1280,
			unsigned int height = 720)
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
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// window attributes
		virtual void SetEventCallBack(const EventCallBackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());


	};
}