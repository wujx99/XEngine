#pragma once

#include "entt.hpp"

#include "XEngine/Core/TimeStep.h"

namespace XEg
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(TimeStep ts);
		void OnViewportResize(uint32_t width, uint32_t height);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};
}
