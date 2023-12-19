#include "xepch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>
namespace XEg
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:m_ProjMatrix(glm::ortho(left, right, bottom, top, -1.f, 1.f)), m_ViewMatrix(1.f)
	{
		m_ViewProjMatrix = m_ViewMatrix * m_ProjMatrix;
	}
	void OrthographicCamera::ReCalcViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_Position) 
			* glm::rotate(glm::mat4(1.f),glm::radians(m_Rotation),glm::vec3(0,0,1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjMatrix = m_ViewMatrix * m_ProjMatrix;
	}
}