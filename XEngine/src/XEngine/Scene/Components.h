#pragma once

#include "XEngine/Renderer/Camera.h"
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
		Camera Camera;
		bool Primary = true;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const glm::mat4& projection)
			:Camera(projection)
		{
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