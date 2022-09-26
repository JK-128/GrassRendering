#include "Camera.h"

Camera::Camera()
{
	m_pos    = glm::vec3(0.0f, 0.0f,  3.0f);
	m_front  = glm::vec3(0.0f, 0.0f, -1.0f);
	m_cUp    = glm::vec3(0.0f, 1.0f,  0.0f);
	m_target = glm::vec3(0.0f, 0.0f,  0.0f);

	m_dir   = glm::normalize(m_pos - m_target);
	m_right = glm::normalize(glm::cross(m_cUp, m_dir));
	m_wUp   = glm::cross(m_dir, m_right);

	updateVectors();
}

glm::mat4 Camera::getView()
{
	return m_view;
}

glm::vec3 Camera::getFront()
{
	return m_front;
}

glm::vec3 Camera::getPos()
{
	return m_pos;
}

glm::vec3 Camera::getCUp()
{
	return m_cUp;
}

void Camera::update()
{
	m_view = glm::lookAt(m_pos, m_pos + m_front, m_cUp);
}

void Camera::updateVectors()
{
	glm::vec3 front = glm::vec3(0.0f);

	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	
	m_front = glm::normalize(front);
	m_right = glm::normalize(glm::cross(m_front, m_wUp));
	m_cUp   = glm::normalize(glm::cross(m_right, m_front));

	update();
}

void Camera::move()
{
	float velocity = m_moveSpeed * (float)deltaTime;

	if      (camForward)  m_pos += m_front * velocity;
	else if (camBackward) m_pos -= m_front * velocity;
	else if (camLeft)     m_pos -= m_right * velocity;
	else if (camRight)    m_pos += m_right * velocity;
	else if (camUp)       m_pos += m_wUp * velocity;
	else if (camDown)     m_pos -= m_wUp * velocity;

	update();
}

void Camera::look()
{
	if (moved)
	{
		moved = false;

		m_yaw += (float)xOffset * m_lookSpeed * (float)deltaTime;
		m_pitch += (float)yOffset * m_lookSpeed * (float)deltaTime;

		if (m_pitch > 89.0f) m_pitch = 89.0f;
		if (m_pitch < -89.0f) m_pitch = -89.0f;

		if (m_yaw > 360.0f) m_yaw -= 360.0f;
		if (m_yaw < -360.0f) m_yaw += 360.0f;

		updateVectors();
	}
}