#pragma once

#include "Events/Event.h"

namespace Pixie
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		static EventType StaticType() { return EventType::WindowClose; }
		EventType GetEventType() const override { return StaticType(); }
		const char* GetName() const override { return "WindowClose"; }
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height){}

		static EventType StaticType() { return EventType::WindowResize; }
		EventType GetEventType() const override { return StaticType(); }
		const char* GetName() const override { return "WindowResize"; }

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

	private:
		uint32_t m_Width, m_Height;
	};
}
