#pragma once

#include "SceneCamera.h"
#include "XEngine/Scene/ScriptableEntity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace XEg
{
	struct TagComponnent
	{
		std::string Tag;

		TagComponnent() = default;
		TagComponnent(const TagComponnent&) = default;
		TagComponnent(const std::string& tag)
			:Tag(tag)
		{

		}
	};
	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		

	};

	struct NativeScriptComponent
	{
		ScriptaleEntity* Instance = nullptr;

		ScriptaleEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() {return static_cast<ScriptaleEntity*>( new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) {delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
	struct TransformComponent
	{
		glm::vec3 Translation { 0.f, 0.f, 0.f };
		glm::vec3 Rotation { 0.f, 0.f, 0.f };
		glm::vec3 Scale { 1.f, 1.f, 1.f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent& transform) = default;
		TransformComponent(const glm::vec3& translation)
			:Translation(translation)
		{

		}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::rotate(glm::mat4(1.f), Rotation.x, { 1, 0, 0 })
			* glm::rotate(glm::mat4(1.f), Rotation.y, { 0, 1, 0 })
			* glm::rotate(glm::mat4(1.f), Rotation.z, { 0, 0, 1 });

			return glm::translate(glm::mat4(1.f), Translation) * rotation * glm::scale(glm::mat4(1.f), Scale);
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.f, 1.f, 1.f, 1.f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4 & color)
			: Color(color) {}
	};
}
