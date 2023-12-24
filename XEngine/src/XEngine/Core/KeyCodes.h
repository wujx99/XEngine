#pragma once

namespace XEg
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348

	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keycode)
	{
		os << static_cast<int32_t>(keycode);
		return os;
	}
}
// From glfw3.h
#define XE_KEY_SPACE           ::XEg::Key::Space
#define XE_KEY_APOSTROPHE      ::XEg::Key::Apostrophe    /* ' */
#define XE_KEY_COMMA           ::XEg::Key::Comma         /* , */
#define XE_KEY_MINUS           ::XEg::Key::Minus         /* - */
#define XE_KEY_PERIOD          ::XEg::Key::Period        /* . */
#define XE_KEY_SLASH           ::XEg::Key::Slash         /* / */
#define XE_KEY_0               ::XEg::Key::D0
#define XE_KEY_1               ::XEg::Key::D1
#define XE_KEY_2               ::XEg::Key::D2
#define XE_KEY_3               ::XEg::Key::D3
#define XE_KEY_4               ::XEg::Key::D4
#define XE_KEY_5               ::XEg::Key::D5
#define XE_KEY_6               ::XEg::Key::D6
#define XE_KEY_7               ::XEg::Key::D7
#define XE_KEY_8               ::XEg::Key::D8
#define XE_KEY_9               ::XEg::Key::D9
#define XE_KEY_SEMICOLON       ::XEg::Key::Semicolon     /* ; */
#define XE_KEY_EQUAL           ::XEg::Key::Equal         /* = */
#define XE_KEY_A               ::XEg::Key::A
#define XE_KEY_B               ::XEg::Key::B
#define XE_KEY_C               ::XEg::Key::C
#define XE_KEY_D               ::XEg::Key::D
#define XE_KEY_E               ::XEg::Key::E
#define XE_KEY_F               ::XEg::Key::F
#define XE_KEY_G               ::XEg::Key::G
#define XE_KEY_H               ::XEg::Key::H
#define XE_KEY_I               ::XEg::Key::I
#define XE_KEY_J               ::XEg::Key::J
#define XE_KEY_K               ::XEg::Key::K
#define XE_KEY_L               ::XEg::Key::L
#define XE_KEY_M               ::XEg::Key::M
#define XE_KEY_N               ::XEg::Key::N
#define XE_KEY_O               ::XEg::Key::O
#define XE_KEY_P               ::XEg::Key::P
#define XE_KEY_Q               ::XEg::Key::Q
#define XE_KEY_R               ::XEg::Key::R
#define XE_KEY_S               ::XEg::Key::S
#define XE_KEY_T               ::XEg::Key::T
#define XE_KEY_U               ::XEg::Key::U
#define XE_KEY_V               ::XEg::Key::V
#define XE_KEY_W               ::XEg::Key::W
#define XE_KEY_X               ::XEg::Key::X
#define XE_KEY_Y               ::XEg::Key::Y
#define XE_KEY_Z               ::XEg::Key::Z
#define XE_KEY_LEFT_BRACKET    ::XEg::Key::LeftBracket   /* [ */
#define XE_KEY_BACKSLASH       ::XEg::Key::Backslash     /* \ */
#define XE_KEY_RIGHT_BRACKET   ::XEg::Key::RightBracket  /* ] */
#define XE_KEY_GRAVE_ACCENT    ::XEg::Key::GraveAccent   /* ` */
#define XE_KEY_WORLD_1         ::XEg::Key::World1        /* non-US #1 */
#define XE_KEY_WORLD_2         ::XEg::Key::World2        /* non-US #2 */

/* Function keys */
#define XE_KEY_ESCAPE          ::XEg::Key::Escape
#define XE_KEY_ENTER           ::XEg::Key::Enter
#define XE_KEY_TAB             ::XEg::Key::Tab
#define XE_KEY_BACKSPACE       ::XEg::Key::Backspace
#define XE_KEY_INSERT          ::XEg::Key::Insert
#define XE_KEY_DELETE          ::XEg::Key::Delete
#define XE_KEY_RIGHT           ::XEg::Key::Right
#define XE_KEY_LEFT            ::XEg::Key::Left
#define XE_KEY_DOWN            ::XEg::Key::Down
#define XE_KEY_UP              ::XEg::Key::Up
#define XE_KEY_PAGE_UP         ::XEg::Key::PageUp
#define XE_KEY_PAGE_DOWN       ::XEg::Key::PageDown
#define XE_KEY_HOME            ::XEg::Key::Home
#define XE_KEY_END             ::XEg::Key::End
#define XE_KEY_CAPS_LOCK       ::XEg::Key::CapsLock
#define XE_KEY_SCROLL_LOCK     ::XEg::Key::ScrollLock
#define XE_KEY_NUM_LOCK        ::XEg::Key::NumLock
#define XE_KEY_PRINT_SCREEN    ::XEg::Key::PrintScreen
#define XE_KEY_PAUSE           ::XEg::Key::Pause
#define XE_KEY_F1              ::XEg::Key::F1
#define XE_KEY_F2              ::XEg::Key::F2
#define XE_KEY_F3              ::XEg::Key::F3
#define XE_KEY_F4              ::XEg::Key::F4
#define XE_KEY_F5              ::XEg::Key::F5
#define XE_KEY_F6              ::XEg::Key::F6
#define XE_KEY_F7              ::XEg::Key::F7
#define XE_KEY_F8              ::XEg::Key::F8
#define XE_KEY_F9              ::XEg::Key::F9
#define XE_KEY_F10             ::XEg::Key::F10
#define XE_KEY_F11             ::XEg::Key::F11
#define XE_KEY_F12             ::XEg::Key::F12
#define XE_KEY_F13             ::XEg::Key::F13
#define XE_KEY_F14             ::XEg::Key::F14
#define XE_KEY_F15             ::XEg::Key::F15
#define XE_KEY_F16             ::XEg::Key::F16
#define XE_KEY_F17             ::XEg::Key::F17
#define XE_KEY_F18             ::XEg::Key::F18
#define XE_KEY_F19             ::XEg::Key::F19
#define XE_KEY_F20             ::XEg::Key::F20
#define XE_KEY_F21             ::XEg::Key::F21
#define XE_KEY_F22             ::XEg::Key::F22
#define XE_KEY_F23             ::XEg::Key::F23
#define XE_KEY_F24             ::XEg::Key::F24
#define XE_KEY_F25             ::XEg::Key::F25

/* Keypad */
#define XE_KEY_KP_0            ::XEg::Key::KP0
#define XE_KEY_KP_1            ::XEg::Key::KP1
#define XE_KEY_KP_2            ::XEg::Key::KP2
#define XE_KEY_KP_3            ::XEg::Key::KP3
#define XE_KEY_KP_4            ::XEg::Key::KP4
#define XE_KEY_KP_5            ::XEg::Key::KP5
#define XE_KEY_KP_6            ::XEg::Key::KP6
#define XE_KEY_KP_7            ::XEg::Key::KP7
#define XE_KEY_KP_8            ::XEg::Key::KP8
#define XE_KEY_KP_9            ::XEg::Key::KP9
#define XE_KEY_KP_DECIMAL      ::XEg::Key::KPDecimal
#define XE_KEY_KP_DIVIDE       ::XEg::Key::KPDivide
#define XE_KEY_KP_MULTIPLY     ::XEg::Key::KPMultiply
#define XE_KEY_KP_SUBTRACT     ::XEg::Key::KPSubtract
#define XE_KEY_KP_ADD          ::XEg::Key::KPAdd
#define XE_KEY_KP_ENTER        ::XEg::Key::KPEnter
#define XE_KEY_KP_EQUAL        ::XEg::Key::KPEqual

#define XE_KEY_LEFT_SHIFT      ::XEg::Key::LeftShift
#define XE_KEY_LEFT_CONTROL    ::XEg::Key::LeftControl
#define XE_KEY_LEFT_ALT        ::XEg::Key::LeftAlt
#define XE_KEY_LEFT_SUPER      ::XEg::Key::LeftSuper
#define XE_KEY_RIGHT_SHIFT     ::XEg::Key::RightShift
#define XE_KEY_RIGHT_CONTROL   ::XEg::Key::RightControl
#define XE_KEY_RIGHT_ALT       ::XEg::Key::RightAlt
#define XE_KEY_RIGHT_SUPER     ::XEg::Key::RightSuper
#define XE_KEY_MENU            ::XEg::Key::Menu