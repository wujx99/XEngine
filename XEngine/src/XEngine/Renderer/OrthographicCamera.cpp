#include "xepch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>
namespace XEg
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:m_ProjMatrix(glm::ortho(left, right, bottom, top, -1.f, 1.f)), m_ViewMatrix(1.f)
	{
		XE_PROFILE_FUNCTION();

		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		XE_PROFILE_FUNCTION();

		m_ProjMatrix = glm::ortho(left, right, bottom, top, -1.f, 1.f);
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;

	}
	void OrthographicCamera::ReCalcViewMatrix()
	{
		XE_PROFILE_FUNCTION();

		glm::mat4 transform =
			glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation), glm::vec3(0, 0, 1)) * glm::translate(glm::mat4(1.f), m_Position);

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}
}