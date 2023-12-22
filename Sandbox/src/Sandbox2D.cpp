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

	XEg::Renderer2D::BeginScene(m_CameraController.GetCamera());

	XEg::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });

	XEg::Renderer2D::EndScene();


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
