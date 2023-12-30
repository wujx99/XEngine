#pragma once

#include "Event.h"
#include "XEngine/Core/KeyCodes.h"


namespace XEg
{
	class KeyEvent :public Event
	{
	public:
		inline KeyCode GetKeyCode()const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard| EventCategoryInput) // nice
	protected:
		KeyEvent(const KeyCode keyCode)  // only construct by drived class
			:m_KeyCode(keyCode){}
		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keyCode, const uint16_t repeatCount)
			:KeyEvent(keyCode), m_RepeatCount(repeatCount)
		{

		}
		inline uint16_t GetRepeatCount() const { return m_RepeatCount; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:" << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		uint16_t m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keyCode)
			:KeyEvent(keyCode)
		{

		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent:" << m_KeyCode << " released";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keyCode)
			:KeyEvent(keyCode)
		{

		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent:" << m_KeyCode << " typed!";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)

	};
}