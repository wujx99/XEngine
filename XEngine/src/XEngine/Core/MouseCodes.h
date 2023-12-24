#pragma once
#include <cstdint>
#include <iostream>
namespace XEg
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}
#define XE_MOUSE_BUTTON_0      ::XEg::Mouse::Button0
#define XE_MOUSE_BUTTON_1      ::XEg::Mouse::Button1
#define XE_MOUSE_BUTTON_2      ::XEg::Mouse::Button2
#define XE_MOUSE_BUTTON_3      ::XEg::Mouse::Button3
#define XE_MOUSE_BUTTON_4      ::XEg::Mouse::Button4
#define XE_MOUSE_BUTTON_5      ::XEg::Mouse::Button5
#define XE_MOUSE_BUTTON_6      ::XEg::Mouse::Button6
#define XE_MOUSE_BUTTON_7      ::XEg::Mouse::Button7
#define XE_MOUSE_BUTTON_LAST   ::XEg::Mouse::ButtonLast
#define XE_MOUSE_BUTTON_LEFT   ::XEg::Mouse::ButtonLeft
#define XE_MOUSE_BUTTON_RIGHT  ::XEg::Mouse::ButtonRight
#define XE_MOUSE_BUTTON_MIDDLE ::XEg::Mouse::ButtonMiddle