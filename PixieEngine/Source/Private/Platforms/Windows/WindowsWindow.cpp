#include "ppch.h"
#include "Platforms/Windows/WindowsWindow.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Pixie
{
	static bool s_GLFWInitialized = false;
	WindowsWindow::WindowsWindow(const char* title, uint32_t width, uint32_t height, bool vsync)
	{
		Init(title, width, height);
		SetVSync(vsync);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const char* title, uint32_t width, uint32_t height)
	{
		if (!s_GLFWInitialized)
		{
			if (!glfwInit())
			{
				PX_CORE_ASSERT(false, "Could not initialize GLFW!");
			}
			s_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		PX_CORE_ASSERT(m_Window, "Failed to create GLFW window!");

		glfwMakeContextCurrent(m_Window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			PX_CORE_ASSERT(false, "Could not initialize GLAD!");
		}
		glfwSetWindowUserPointer(m_Window, this);

		// Set GLFW callbacks to forward to our Event system.
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				auto windows = (WindowsWindow*)(glfwGetWindowUserPointer(window));
				WindowCloseEvent event;
				windows->m_EventCallback(event);
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				auto windows = (WindowsWindow*)(glfwGetWindowUserPointer(window));
				WindowResizeEvent event((uint32_t) width, (uint32_t) height);
				windows->m_EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto windows = (WindowsWindow*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, false);
					windows->m_EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, true);
					windows->m_EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					windows->m_EventCallback(event);
					break;
				}
				}
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
			{
				auto windows = (WindowsWindow*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)x, (float)y);
				windows->m_EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				auto windows = (WindowsWindow*)glfwGetWindowUserPointer(window);
				if (action == GLFW_PRESS)
				{
					MouseButtonPressedEvent event(button);
					windows->m_EventCallback(event);
				}
				else if (GLFW_RELEASE)
				{
					MouseButtonReleasedEvent event(button);
					windows->m_EventCallback(event);
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				auto windows = (WindowsWindow*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				windows->m_EventCallback(event);
			});

	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	float WindowsWindow::GetTime() const
	{
		return (float)glfwGetTime();
	}
	void WindowsWindow::SetVSync(bool enabled)
	{
		m_VSync = enabled;
		glfwSwapInterval(enabled ? 1 : 0);
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_VSync;
	}
	void WindowsWindow::SetEventCallback(const EventCallbackFn& callback)
	{
		m_EventCallback = callback;
	}

	Window* Window::Create(const char* title, uint32_t width, uint32_t height, bool vsync)
	{
		return new WindowsWindow(title, width, height, vsync);
	}
}