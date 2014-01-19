#include "common/world/components/ai_handler.h"
#include "common/world/world.h"

void AiHandler::tick(float dt, World& w) {
  for (Ai& a : mComponents) {
    Physics* p1 = w.physics().get(a.eid());
    if (!p1) continue;
    Physics* p2 = w.physics().get(a.follow_eid());
    if (!p2) continue;
    p1->position = p2->eye_position();
#if 0
    glm::vec3 delta = p2->position - p1->position;
    p1->velocity += glm::normalize(delta) * ai_speed * dt;
    if (p1->on_ground) {
      p1->velocity.y += 5.0f;
      p1->on_ground = false;
    }
#endif
  }
}
