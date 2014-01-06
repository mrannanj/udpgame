#include "common/world/components/input_handler.h"

void InputHandler::setInputs(const std::vector<InputC>& inputs) {
  mComponents = inputs;
}

InputC* InputHandler::getByClient(int clientId) {
  for (InputC& c : mComponents)
    if (c.mClient == clientId)
      return &c;
  return nullptr;
}
