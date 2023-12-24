#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		:m_Name(name),m_Func(func),m_Stop(false)
	{
		m_TimeBegin = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		if (!m_Stop)
			Stop();
	}
	void Stop()
	{
		auto TimeEnd = std::chrono::high_resolution_clock::now();
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_TimeBegin).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(TimeEnd).time_since_epoch().count();
		m_Stop = true;

		float duration = (end - start) * .001f;
		m_Func({ m_Name, duration });
	}

private:
	const char* m_Name;
	Fn m_Func;
	bool m_Stop;
	std::chrono::time_point<std::chrono::steady_clock> m_TimeBegin;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult){m_ProfileResults.push_back(profileResult);})

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.f/720.f)
{

}
void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = XEg::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(XEg::TimeStep ts)
{
	PROFILE_SCOPE("Sandbox2D::OnUpdate");
	// Update
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}
	// Render
	{
		PROFILE_SCOPE("Render Prep");

		XEg::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		XEg::RenderCommand::Clear();
	}
	{
		PROFILE_SCOPE("Render Draw");

		XEg::Renderer2D::BeginScene(m_CameraController.GetCamera());

		XEg::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		XEg::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		XEg::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);

		XEg::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();
	ImGui::End();
}

void Sandbox2D::OnEvent(XEg::Event& event)
{
	m_CameraController.OnEvent(event);
}
