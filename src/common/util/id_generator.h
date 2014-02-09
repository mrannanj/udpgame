#pragma once

template<typename T>
class IdGen{
public:
  IdGen();
  T generateId();

  void setNext(T);
  T getNext();

private:
  T mNext;
};

template<typename T>
IdGen<T>::IdGen():
  mNext(0)
{
}

template<typename T>
T IdGen<T>::generateId() {
  return mNext++;
}

template<typename T>
void IdGen<T>::setNext(T next) {
  mNext = next;
}

template<typename T>
T IdGen<T>::getNext() {
  return mNext;
}
