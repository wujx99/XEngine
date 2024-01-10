#pragma once

#include "SceneCamera.h"
#include "XEngine/Core/UUID.h"
#include "XEngine/Renderer/Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace XEg
{
	struct IDComponent
	{
		UUID ID;
		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
	};
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
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

	// Forward declaration
	class ScriptaleEntity;

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
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));
			return glm::translate(glm::mat4(1.f), Translation) * rotation * glm::scale(glm::mat4(1.f), Scale);
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.f, 1.f, 1.f, 1.f };

		Ref<Texture2D> Texture;
		float TilingFactor = 1.f;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4 & color)
			: Color(color) {}
	};

	struct CircleRendererComponent
	{
		glm::vec4 Color{ 1.f, 1.f, 1.f, 1.f };
		float Thickness = 1.f;
		float Fade = 0.005f;
		CircleRendererComponent() = default;
		CircleRendererComponent(const CircleRendererComponent&) = default;
	};
	// Physics
	struct Rigidbody2DComponent
	{
		enum class BodyType {
			Static = 0, Dynamic, Kinematic
		};
		BodyType Type = BodyType::Static;
		bool FixedRotation = false;

		// Storage for runtime
		void* RuntimeBody = nullptr;

		Rigidbody2DComponent() = default;
		Rigidbody2DComponent(const Rigidbody2DComponent&) = default;
	};

	struct BoxCollider2DComponent
	{
		glm::vec2 Offset = { 0.f, 0.f };
		glm::vec2 Size = { 0.5f, 0.5f };

		// TODO: move into physics material in the future
		float Density = 1.f;
		float Friction = 0.5f;
		float Restitution = 0.f;
		float RestitutionThreshold = 0.5f;

		// Storage for runtime
		void* RuntimeFixture = nullptr;
		BoxCollider2DComponent() = default;
		BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
	};
}
