#include "xepch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "Renderer2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace XEg
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjMatrix = camera.GetViewProjMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjMatrix);

		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}