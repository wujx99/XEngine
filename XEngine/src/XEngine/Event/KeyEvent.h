#pragma once

#include "Event.h"



namespace XEg
{
	class KeyEvent :public Event
	{
	public:
		inline int GetKeyCode()const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard| EventCategoryInput) // nice
	protected:
		KeyEvent(int keyCode)  // only construct by drived class
			:m_KeyCode(keyCode){}
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			:KeyEvent(keyCode), m_RepeatCount(repeatCount)
		{

		}
		inline int GetRepeatCount() const { return m_RepeatCount; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:" << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
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
		KeyTypedEvent(int keyCode)
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