#pragma once
#include "XEngine/Core/TimeStep.h"
#include "XEngine/Core/UUID.h"
#include "XEngine/Renderer/EditorCamera.h"

#include "entt.hpp"

class b2World;

namespace XEg
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();
		
		static Ref<Scene> Copy(Ref<Scene> other);

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnSimulationStart();
		void OnSimulationStop();

		void OnUpdateRuntime(TimeStep ts);
		void OnUpdateSimulation(TimeStep ts, EditorCamera& camera);
		void OnUpdateEditor(TimeStep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		void DuplicateEntity(Entity entity);
		Entity GetPrimaryCameraEntity();
		template<typename... Components>
		auto GetAllEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

		void OnPhysics2DStart();
		void OnPhysics2DStop();

		void RenderScene(EditorCamera& camera);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight;

		b2World* m_PhysicsWorld = nullptr;

		friend class Entity;
		friend class SceneHierarchyPanel;
		friend class SceneSerializer;
	};



}
