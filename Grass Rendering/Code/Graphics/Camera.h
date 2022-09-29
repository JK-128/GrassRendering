#pragma once
#include "../../Dependencies/glm/glm/gtc/matrix_transform.hpp"
#include "../../Dependencies/glm/glm/gtc/type_ptr.hpp"

#include "../Utility/Logger.h"
#include "../Utility/DeltaTime.h"
#include "../Utility/Input.h"

class Camera
{
private:
	glm::vec3 m_pos;
	glm::vec3 m_front;
	glm::vec3 m_target;
	glm::vec3 m_dir;
	glm::vec3 m_cUp;
	glm::vec3 m_wUp;
	glm::vec3 m_right;

	glm::mat4 m_view;

	float m_moveSpeed =  2.5f;
	float m_lookSpeed =  100.0f;
	float m_yaw       = -90.0f;
	float m_pitch     =   0.0f;

public:
	Camera();

	glm::mat4 getView();

	glm::vec3 getFront();
	glm::vec3 getPos();
	glm::vec3 getCUp();

	void update();
	void updateVectors();
	void move();
	void look();
};

