#include "camera.h"

void Camera::makeOthogonal()
{
	m_look = glm::normalize(m_look);
	m_up = glm::cross(m_look, m_right);
	m_right = glm::cross(m_up, m_look);
	m_up = glm::normalize(m_up);
	m_right = glm::normalize(m_right);
}
void Camera::calculateViewMatrix()
{
	makeOthogonal();

	glm::mat4 orientation(
		m_right.x, m_up.x, m_look.x, 0.0f,
		m_right.y, m_up.y, m_look.y, 0.0f,
		m_right.z, m_up.z, m_look.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);
	glm::mat4 translation (
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-m_position.x, -m_position.y, -m_position.z, 1.0f
		);

	m_viewMatrix = translation * orientation;
}