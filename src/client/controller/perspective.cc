#include <iostream>
#include <sstream>
#define GLM_FORCE_RADIANS 1
#include <glm/gtc/matrix_transform.hpp>

#include "client/view/window.h"
#include "client/controller/input/input.h"
#include "client/controller/perspective.h"

#include "common/world/world.h"
#include "common/world/components/grid_handler.h"
#include "common/world/components/physics_handler.h"

Perspective::Perspective():
	mClientMode(ClientMode::MODE_OBSERVER),
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

void Perspective::handle_input(Input& i)
{
	if (mClientMode == ClientMode::MODE_OBSERVER)
		handle_freelook_input(i);
}

// FIXME: how to avoid duplicate code here and in input manager
void Perspective::handle_freelook_input(const Input& input)
{
	float move_speed = 0.1f;
	m_vertical_angle -= (float) input.mouse_delta_y * 0.01f;
	m_horizontal_angle -= (float) input.mouse_delta_x * 0.01f;

	m_direction =
		glm::vec3(cos(m_vertical_angle) * sin(m_horizontal_angle),
				sin(m_vertical_angle),
				cos(m_vertical_angle) * cos(m_horizontal_angle)
			 );

	glm::vec3 right = glm::vec3(sin(m_horizontal_angle - 3.14f / 2.0f),
			0, cos(m_horizontal_angle - 3.14f / 2.0f)
			);
	m_up = glm::cross(right, m_direction);

	if (input.continous_actions & ContinousAction::MOVE_FORWARD) {
		m_position += m_direction * move_speed;
	} else if (input.continous_actions & ContinousAction::MOVE_BACK) {
		m_position -= m_direction * move_speed;
	}
	if (input.continous_actions & ContinousAction::MOVE_RIGHT) {
		m_position += right * move_speed;
	} else if (input.continous_actions & ContinousAction::MOVE_LEFT) {
		m_position -= right * move_speed;
	}
	if (input.continous_actions & ContinousAction::JUMP) {
		m_position.y += move_speed;
	}
}

void Perspective::tick(World& w)
{
	m_projection = glm::perspective(45.0f,
			(float) window_width / window_height,
			0.1f, 100.0f);
	if (mClientMode == ClientMode::MODE_PLAYER) {
		Physics *p = (Physics *) w.physics().get(m_follow_id);
		if (p) {
			m_horizontal_angle = p->horizontal_angle;
			m_vertical_angle = p->vertical_angle;
			m_position = p->eye_position();
			m_direction = p->look_direction();
			glm::vec3 right =
				glm::vec3(sin(m_horizontal_angle - 3.14f / 2.0f),
					  0, cos(m_horizontal_angle - 3.14f / 2.0f));
			m_up = glm::cross(right, m_direction);
		}
	}
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
