#pragma once
#include "XEngine/Core/Base.h"
#include "XEngine/Core/KeyCodes.h"
#include "XEngine/Core/MouseCodes.h"

namespace XEg
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}