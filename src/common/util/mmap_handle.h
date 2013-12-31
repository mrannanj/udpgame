#pragma once

#include <stddef.h>

class MmapHandle {
public:
  MmapHandle(const char*);
  ~MmapHandle();

  int fd() const;
  size_t size() const;
  void* ptr() const;

private:
  int m_fd;
  size_t m_size;
  void* m_ptr;
};
