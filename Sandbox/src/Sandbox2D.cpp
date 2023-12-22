#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.f/720.f)
{

}
void Sandbox2D::OnAttach()
{
	m_SquareVA = XEg::VertexArray::Create();

	float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	XEg::Ref<XEg::VertexBuffer> squareVB;
	squareVB.reset(XEg::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ XEg::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	XEg::Ref<XEg::IndexBuffer> squareIB;
	squareIB.reset(XEg::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = XEg::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(XEg::TimeStep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	XEg::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	XEg::RenderCommand::Clear();

	XEg::Renderer::BeginScene(m_CameraController.GetCamera());

	m_FlatColorShader->Bind();
	std::dynamic_pointer_cast<XEg::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	XEg::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	XEg::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(XEg::Event& event)
{
	m_CameraController.OnEvent(event);
}
