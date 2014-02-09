#pragma once

#if 0
#include <stddef.h>

class MmapHandle {
public:
  MmapHandle(const char*);
  ~MmapHandle();

  MmapHandle(const MmapHandle&) = delete;
  MmapHandle& operator=(const MmapHandle&) = delete;

  int fd() const;
  size_t size() const;
  void* ptr() const;

private:
  int m_fd;
  size_t m_size;
  void* m_ptr;
};
#endif
