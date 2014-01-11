#include "common/world/components/input_handler.h"
#include "common/world/world.h"

#include <iostream>
#include <cstdlib>

using namespace std;

void InputHandler::tick(float, World& w) {
  for (FrameInput& fi : mComponents) {
    if (w.client().getByClient(fi.client())) continue;
    ClientData cd;
    cd.set_dead(true);
    cd.set_mode(ClientMode::MODE_PLAYER);
    cd.set_client(fi.client());
    fi.set_eid(cd.eid());
    w.client().add(cd);
  }
}

FrameInput* InputHandler::getByClient(int clientId) {
  for (FrameInput& f : mComponents)
    if (f.client() == clientId)
      return &f;
  return nullptr;
}
