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

    Inventory* inv = w.inventory().get(id);
    if (inv == nullptr) continue;

    if ((i.actions & ContinousAction::FIRST) or
        i.actions & ContinousAction::SECOND)
    {
      glm::vec3 pos = p->eye_position();
      glm::vec3 dir = p->look_direction();
      float distance;
      char* hitBlock;
      char* faceBlock;
      if (w.grid().raycast(pos, dir, distance, &hitBlock, &faceBlock)) {
        if (i.actions & ContinousAction::FIRST) {
          *hitBlock = 0;
        }
        if (i.actions & ContinousAction::SECOND and faceBlock != nullptr) {
          *faceBlock = inv->mWielding;
        }
      }
    }
    if (i.actions & ContinousAction::ITEM_1)
      inv->mWielding = 1;
    if (i.actions & ContinousAction::ITEM_2)
      inv->mWielding = 2;
    if (i.actions & ContinousAction::ITEM_3)
      inv->mWielding = 3;
  }
}
