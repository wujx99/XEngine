#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>





Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.f/720.f)
{

}
void Sandbox2D::OnAttach()
{
	XE_PROFILE_FUNCTION();

	m_CheckerboardTexture = XEg::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	XE_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(XEg::TimeStep ts)
{
	XE_PROFILE_FUNCTION();
	// Update
	
	m_CameraController.OnUpdate(ts);
	
	// Render
	{
		XE_PROFILE_SCOPE("Render Prep");

		XEg::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		XEg::RenderCommand::Clear();
	}
	{
		XE_PROFILE_SCOPE("Render Draw");

		XEg::Renderer2D::BeginScene(m_CameraController.GetCamera());

		// XEg::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		XEg::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		XEg::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		XEg::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 1.0f);
		XEg::Renderer2D::DrawQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture, 1.0f);

		XEg::Renderer2D::EndScene();
	}
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
