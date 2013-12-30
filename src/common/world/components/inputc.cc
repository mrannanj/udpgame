#include "common/world/components/inputc.h"

InputC::InputC():
  id(0),
  actions(0),
  horizontal_angle_delta(0.0f),
  vertical_angle_delta(0.0f)
{
}

InputC::InputC(const Input& i):
  id(0),
  actions(i.continous_actions),
  horizontal_angle_delta((float)i.mouse_delta_x * 0.01f),
  vertical_angle_delta((float)i.mouse_delta_y * 0.01f)
{
}
