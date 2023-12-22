#pragma once
#include "XEngine/Renderer/RendererAPI.h"
#include "XEngine/Renderer/OrthographicCamera.h"
#include "XEngine/Renderer/Shader.h"
namespace XEg
{
	

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray,
			const glm::mat4& transform = glm::mat4(1.f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjMatrix;
		};
		static Scope<SceneData> s_SceneData;
	};
}