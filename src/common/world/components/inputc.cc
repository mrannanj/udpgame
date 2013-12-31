#include "common/world/components/inputc.h"

InputC::InputC():
  id(0),
  actions(0),
  horizontal_angle_delta(0.0f),
  vertical_angle_delta(0.0f)
{
}

InputC::InputC(const ClientInput& ci):
  id(0),
  actions(ci.actions()),
  horizontal_angle_delta(ci.horizontal_delta()),
  vertical_angle_delta(ci.verical_delta())
{
}

InputC::InputC(const Input& i):
  id(0),
  actions(i.continous_actions),
  horizontal_angle_delta((float)i.mouse_delta_x * 0.01f),
  vertical_angle_delta((float)i.mouse_delta_y * 0.01f)
{
}

std::ostream& operator<<(std::ostream& os, const InputC& ic) {
  os << "id: " << ic.id << std::endl;
  os << "actions: " << ic.actions << std::endl;
  os << "horizontal_delta: " << ic.horizontal_angle_delta << std::endl;
  os << "vertical_delta: " << ic.vertical_angle_delta << std::endl;
  return os;
}
