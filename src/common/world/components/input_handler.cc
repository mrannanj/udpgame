#include "common/world/components/input_handler.h"
#include "common/world/world.h"

#include <iostream>
#include <cstdlib>

void InputHandler::tick(float, World& w) {
  for (FrameInput& fi : mComponents) {
    if (w.client().getByClient(fi.client())) continue;
    ClientData cd;
    cd.set_dead(true);
    cd.set_mode(ClientMode::PLAYER);
    cd.set_client(fi.client());
    w.client().add(cd);
  }
}

FrameInput* InputHandler::getByClient(int clientId) {
  for (FrameInput& f : mComponents)
    if (f.client() == clientId)
      return &f;
  return nullptr;
}

void InputHandler::deserialize(
    const google::protobuf::RepeatedPtrField<FrameInput>& invs)
{
  mComponents.clear();
  for (const FrameInput& i : invs)
    mComponents.push_back(i);
}
