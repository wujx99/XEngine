#pragma once
#include <glm/glm.hpp>
#include "XEngine/Core/KeyCodes.h"
#include "XEngine/Core/MouseCodes.h"

namespace XEg
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
