#pragma once
#include "../../Dependencies/glm/glm/gtc/matrix_transform.hpp"
#include "../../Dependencies/glm/glm/gtc/type_ptr.hpp"

#include "../Utility/Logger.h"
#include "../Utility/DeltaTime.h"
#include "../Utility/Input.h"

class Camera
{
private:
	glm::dvec3 m_pos;
	glm::dvec3 m_front;
	glm::dvec3 m_target;
	glm::dvec3 m_dir;
	glm::dvec3 m_cUp;
	glm::dvec3 m_wUp;
	glm::dvec3 m_right;

	glm::mat4 m_view;

	double m_moveSpeed =   2.5;
	double m_lookSpeed =   5.0;
	double m_yaw       = -90.0;
	double m_pitch     =   0.0;

public:
	Camera();

	glm::mat4 getView();

	glm::vec3 getFront();
	glm::vec3 getPos();
	glm::vec3 getCUp();

	double getMoveSpeed();
	double getLookSpeed();

	void setMoveSpeed(float speed);
	void setLookSpeed(float speed);
	void update();
	void updateVectors();
	void move();
	void look();
};

