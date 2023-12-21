#pragma once
#include "XEngine/Renderer/OrthographicCamera.h"

#include "XEngine/Core/TimeStep.h"

#include "XEngine/Event/MouseEvent.h"
#include "XEngine/Event/ApplicationEvent.h"
namespace XEg
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRation, bool rotation = false);
		
		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);

		// can modify
		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition{ 0.f, 0.f, 0.f };
		float m_CameraRotation{ 0.f };
		
		float m_CameraTranslationSpeed{ 5.f };
		float m_CameraRotationSpeed{ 180.f };
	};
}