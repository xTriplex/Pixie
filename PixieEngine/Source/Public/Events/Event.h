#pragma once

#include "Core/Core.h"
#include <functional>

namespace Pixie
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;

		bool Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T, typename Fn>
		bool Dispatch(const Fn& fn)
		{
			if (m_Event.GetEventType() == T::StaticType())
			{
				m_Event.Handled = fn(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
}
