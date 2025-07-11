#pragma once

#include "Core/Core.h"
#include "Events/Event.h"
#include <functional>
#include <string>

namespace Pixie
{
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual float GetTime() const = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		static Window* Create(const char* title,
							  uint32_t width,
							  uint32_t height,
							  bool vsync = true);
	};
}
