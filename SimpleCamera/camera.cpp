#include "camera.h"
#include <glm\gtx\rotate_vector.hpp>

void Camera::walk(float units)
{
	m_position += m_look * units;
}
void Camera::strafe(float units)
{
	m_position += m_right * units;
}
void Camera::fly(float units)
{
	m_position += m_up * units;
}
void Camera::pitch(float units)
{
	glm::rotate(m_look, units, m_right);
	glm::rotate(m_up, units, m_right);
}
void Camera::yaw(float units)
{
	glm::rotate(m_right, units, m_up);
	glm::rotate(m_look, units, m_up);
}
void Camera::roll(float units)
{
	glm::rotate(m_right, units, m_look);
	glm::rotate(m_up, units, m_look);
}
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
	// By making the right, up and look vectors othonormal unit vectors, 
	// the vectors make up a orthogonal matrix where A-1 = AT
	makeOthogonal();

	// Calculate the oientation matrix which describes how the camera is rotated
	glm::mat4 orientation(
		m_right.x, m_up.x, m_look.x, 0.0f,
		m_right.y, m_up.y, m_look.y, 0.0f,
		m_right.z, m_up.z, m_look.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);

	// Calculate the translation matrix which gives the translation of the camera position
	glm::mat4 translation (
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-m_position.x, -m_position.y, -m_position.z, 1.0f
		);

	// View Matrix = Camera Translation * Camera Orientation
	// We multiply with the translation matrix first because
	m_viewMatrix = translation * orientation;
}

