#pragma once

#include "Events/Event.h"

namespace Pixie
{
	class KeyEvent : public Event
	{
	public:
		int GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, bool repeat)
			: KeyEvent(keycode), m_Repeat(repeat) {}

		static EventType StaticType() { return EventType::KeyPressed; }
		EventType GetEventType() const override { return StaticType(); }
		const char* GetName() const override { return "KeyPressed"; }

		bool IsRepeat() const { return m_Repeat; }
	private:
		bool m_Repeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		static EventType StaticType() { return EventType::KeyReleased; }
		EventType GetEventType() const override { return StaticType(); }
		const char* GetName() const override { return "KeyReleased"; }

	};
}
