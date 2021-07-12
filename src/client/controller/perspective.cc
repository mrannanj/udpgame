#include <iostream>
#include <sstream>
#define GLM_FORCE_RADIANS 1
#include <glm/gtc/matrix_transform.hpp>

#include "client/view/window.h"
#include "client/controller/input/input.h"
#include "client/controller/perspective.h"

#include "common/world/world.h"
#include "common/world/components/grid_handler.h"

Perspective::Perspective():
	m_follow_id(0),
	m_vertical_angle(0.0f),
	m_horizontal_angle(0.0f),
	m_position(2.0f, 5.0f, 2.0f),
	m_direction(),
	m_up(0.0f, 1.0f, 0.0f),
	m_view(),
	m_projection(),
	m_view_projection()
{
}

void Perspective::tick(World& w)
{
	m_projection = glm::perspective(45.0f,
			(float) window_width / window_height,
			0.1f, 100.0f);
	if (fabsf(m_direction.x) <= FLT_MIN
	    or fabsf(m_direction.y) <= FLT_MIN
	    or fabsf(m_direction.z) <= FLT_MIN) {
		m_direction = glm::vec3(1.0, 1.0, 1.0);
	}

	m_view = glm::lookAt(m_position, m_position + m_direction, m_up);
	m_view_projection = m_projection * m_view;
}

const glm::mat4& Perspective::view() const
{
	return m_view;
}

const glm::mat4& Perspective::projection() const
{
	return m_projection;
}

const glm::mat4& Perspective::get_view_projection_matrix() const
{
	return m_view_projection;
}

std::string Perspective::pos_string()const
{
	std::stringstream ss;
	ss << "(" << (int) m_position.x << "," << (int) m_position.y
	   << "," << (int) m_position.z << ")";
	return ss.str();
}
