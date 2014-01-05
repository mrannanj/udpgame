#include "client/controller/screen_stack.h"

ScreenStack g_screen_stack;

ScreenStack::ScreenStack():
  m_dirty(false)
{
}

void ScreenStack::push(Screen* s) {
  m_dirty = true;
  m_screen_stack.push_back(s);
}

void ScreenStack::switch_state(Screen* s) {
  m_dirty = true;
  m_screen_stack.clear();
  m_screen_stack.push_back(s);
}

bool ScreenStack::empty() const {
  return m_screen_stack.empty();
}

Screen* ScreenStack::back() {
  return m_screen_stack.back();
}

void ScreenStack::pop() {
  m_dirty = true;
  m_screen_stack.pop_back();
}

void ScreenStack::clear() {
  m_dirty = true;
  m_screen_stack.clear();
}

bool ScreenStack::check_dirty() {
  bool retval = m_dirty;
  m_dirty = false;
  return retval;
}
