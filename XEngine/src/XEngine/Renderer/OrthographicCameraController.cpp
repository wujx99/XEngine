#include "xepch.h"
#include "OrthographicCameraController.h"

#include "XEngine/Core/Input.h"
#include "XEngine/Core/KeyCodes.h"

namespace XEg
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio),
		m_Camera(-m_AspectRatio*m_ZoomLevel, m_AspectRatio * m_ZoomLevel,  -m_ZoomLevel,  m_ZoomLevel ),
		m_Rotation(rotation)
	{

	}
	void OrthographicCameraController::OnUpdate(TimeStep ts)
	{
		XE_PROFILE_FUNCTION();

		if (XEg::Input::IsKeyPressed(XE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (XEg::Input::IsKeyPressed(XE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (XEg::Input::IsKeyPressed(XE_KEY_UP))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (XEg::Input::IsKeyPressed(XE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (XEg::Input::IsKeyPressed(XE_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (XEg::Input::IsKeyPressed(XE_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}
		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		XE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(XE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(XE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}
	void OrthographicCameraController::OnResize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		XE_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetOffsetY() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		XE_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
}