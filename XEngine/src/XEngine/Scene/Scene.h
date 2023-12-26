#pragma once

#include "entt.hpp"

#include "XEngine/Core/TimeStep.h"

namespace XEg
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		// TEMP
		entt::registry& Reg(){return m_Registry;}

		void OnUpdate(TimeStep ts);
	private:
		entt::registry m_Registry;
	};
}