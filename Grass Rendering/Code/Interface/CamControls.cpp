#include "CamControls.h"


void CamControls::draw()
{
	if (!m_hasCamera)
	{
		logMessage("Attempting to get info from unattached camera.", "CCTR", 1);
		return;
	}

	if (ImGui::CollapsingHeader("Camera"))
	{
		m_moveSpeed = m_cam->getMoveSpeed();
		m_lookSpeed = m_cam->getLookSpeed();

		floatProp("Move Speed:", "ms", &m_moveSpeed, 0.5f, false);
		floatProp("Look Speed:", "ls", &m_lookSpeed, 0.5f, false);

		m_cam->setMoveSpeed(m_moveSpeed);
		m_cam->setLookSpeed(m_lookSpeed);
	}
}

void CamControls::attachCamera(Camera* camera)
{
	m_cam = camera;
	m_hasCamera = true;
}