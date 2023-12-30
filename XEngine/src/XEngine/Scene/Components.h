#pragma once

#include "SceneCamera.h"
#include "XEngine/Scene/ScriptableEntity.h"

#include <glm/glm.hpp>

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
		glm::mat4 Transform{ 1.f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent& transform) = default;
		TransformComponent(const glm::mat4& transform)
			:Transform(transform)
		{

		}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
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
