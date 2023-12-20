#pragma once
#include "RendererAPI.h"
#include "OrthographicCamera.h"
#include "Shader.h"
namespace XEg
{
	

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexArray,
			const glm::mat4& transform = glm::mat4(1.f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjMatrix;
		};
		static SceneData* m_SceneData;
	};
}