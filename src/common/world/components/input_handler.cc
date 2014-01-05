#include "common/world/components/input_handler.h"
#include "common/world/components/grid_handler.h"
#include "common/world/world.h"
#include <iostream>

constexpr float HALF_PI = (float)M_PI/2.0f;
constexpr float PI = (float)M_PI;

using namespace std;

void InputHandler::tick(const std::vector<InputC>& inputs, World& w) {
  float move_speed = 1.5f;
  float jump_velocity = 5.0f;

  for (const InputC& i : inputs) {
    if (i.actions & ContinousAction::SPAWN_UNIT) {
      w.spawn_entity(i.mClient);
    }
    auto it = w.mClient2Entity.find(i.mClient);
    if (it == w.mClient2Entity.end())
      continue;
    EntityId id = it->second;

    PhysicsC* p = w.physics().get(id);
    if (p == nullptr) continue;
    p->horizontal_angle -= i.horizontal_angle_delta;
    p->vertical_angle -= i.vertical_angle_delta;
    if (p->vertical_angle < -HALF_PI)
      p->vertical_angle = -HALF_PI;
    else if (p->vertical_angle > HALF_PI)
      p->vertical_angle = HALF_PI;

    glm::vec3 forward = glm::vec3(
      sin(p->horizontal_angle), 0.0f, cos(p->horizontal_angle));

    glm::vec3 right = glm::vec3(
      sin(p->horizontal_angle - HALF_PI),
      0.0f,
      cos(p->horizontal_angle - HALF_PI)
    );

    if (i.actions & ContinousAction::MOVE_FORWARD)
      p->velocity += forward * move_speed;
    else if (i.actions & ContinousAction::MOVE_BACK)
      p->velocity -= forward * move_speed;

    if (i.actions & ContinousAction::MOVE_RIGHT)
      p->velocity += right * move_speed;
    else if (i.actions & ContinousAction::MOVE_LEFT)
      p->velocity -= right * move_speed;

    if (i.actions & ContinousAction::JUMP && p->on_ground) {
      p->velocity.y += jump_velocity;
      p->on_ground = false;
    }

    if ((i.actions & ContinousAction::FIRST) or
        i.actions & ContinousAction::SECOND)
    {
      glm::vec3 eye_pos = p->position;
      eye_pos.y += 0.7f;
      glm::vec3 dir = glm::vec3(
        cos(p->vertical_angle) * sin(p->horizontal_angle),
        sin(p->vertical_angle),
        cos(p->vertical_angle) * cos(p->horizontal_angle)
      );
      float distance;
      char* hitBlock;
      char* faceBlock;
      if (w.grid().raycast(eye_pos, dir, distance, &hitBlock, &faceBlock)) {
        if (i.actions & ContinousAction::FIRST) {
          *hitBlock = 0;
        }
        if (i.actions & ContinousAction::SECOND and faceBlock != nullptr) {
          *faceBlock = 1;
        }
      }
    }
  }
}
