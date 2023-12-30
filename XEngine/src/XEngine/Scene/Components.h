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

		std::function<void()> InstantiateFunction;
		std::function<void()> DestryInstanceFunction;

		std::function<void(ScriptaleEntity*)> OnCreateFunction;
		std::function<void(ScriptaleEntity*)> OnDestoryFunction;
		std::function<void(ScriptaleEntity*, TimeStep)> OnUpdateFunction;

		template<typename T>
		void Bind()
		{
			InstantiateFunction = [&]() {Instance = new T(); };
			DestryInstanceFunction = [&]() {delete (T*)Instance; Instance = nullptr; };
			OnCreateFunction = [](ScriptaleEntity* instance) {((T*)instance)->OnCreate(); };
			OnDestoryFunction = [](ScriptaleEntity* instance) {((T*)instance)->OnDestroy(); };
			OnUpdateFunction = [](ScriptaleEntity* instance, TimeStep ts) {((T*)instance)->OnUpdate(ts); };
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