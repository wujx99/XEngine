#pragma once

#include "Scene.h"

#include <entt.hpp>

namespace XEg
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			XE_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded(*this, component);

			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			XE_CORE_ASSERT(HasComponent<T>(), "Entity dose not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			XE_CORE_ASSERT(HasComponent<T>(), "Entity dose not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		operator entt::entity() const { return m_EntityHandle; }

		bool operator==(const Entity& other)
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}
		bool operator!=(const Entity& other)
		{
			return !(*this == other);
		}
	private:
		entt::entity m_EntityHandle{ entt::null};

		Scene* m_Scene = nullptr;
	};

}
