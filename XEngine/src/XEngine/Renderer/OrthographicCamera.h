#pragma once

#include <glm/glm.hpp>

namespace XEg
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		
		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline float GetRotation() const { return m_Rotation; }

		void SetProjection(float left, float right, float bottom, float top);
		void SetPosition(const glm::vec3& position) { m_Position = position; ReCalcViewMatrix(); };
		void SetRotation(float rotation) { m_Rotation = rotation;  ReCalcViewMatrix(); }

		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetProjMatrix() const { return m_ProjMatrix; }
		inline const glm::mat4& GetViewProjMatrix() const { return m_ViewProjMatrix; }
	private:
		void ReCalcViewMatrix();
		glm::vec3 m_Position{ 0,0,0 };
		float m_Rotation{ 0.f };

		glm::mat4 m_ProjMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjMatrix;
	};
}