#include "xepch.h"

#include "Scene.h"
#include "XEngine/Scene/Components.h"
#include "XEngine/Renderer/Renderer2D.h"

#include <glm/glm.hpp>
#include "XEngine/Scene/Entity.h"

namespace XEg
{
	
	Scene::Scene()
	{

	}
	Scene::~Scene()
	{
	}
	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this }; // use this to bind Scene
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponnent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}
	void Scene::OnUpdate(TimeStep ts)
	{
		// update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					if (!nsc.Instance)
					{
						nsc.Instance  = nsc.InstantiateScript();
						nsc.Instance->m_Entity = Entity{ entity, this };
						nsc.Instance->OnCreate();
					}
				
					nsc.Instance->OnUpdate(ts);
				});
		}


		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;

		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}
		if(mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, *cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize out non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
			{
				cameraComponent.Camera.SetViewportSize(width, height);
			}
		}
	}

}
