#pragma once

#include "Core/Core.h"
#include "Platforms/Window.h"
#include <GLFW/glfw3.h>

namespace Pixie
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const char* title, uint32_t width, uint32_t height, bool vsync);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;
		virtual float GetTime() const override;
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
		virtual void SetEventCallback(const EventCallbackFn& callback) override;

	private:
		void Init(const char* title, uint32_t width, uint32_t height);
		void Shutdown();

	private:
		GLFWwindow*     m_Window = nullptr;
		EventCallbackFn m_EventCallback;
		bool            m_VSync = true;
	};
}
