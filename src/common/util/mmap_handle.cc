#include <assert.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "common/util/mmap_handle.h"

MmapHandle::MmapHandle(const char* filename):
  m_fd(-1),
  m_ptr(nullptr)
{
  m_fd = open(filename, 0, O_RDONLY);
  assert(m_fd >= 0);
  off_t size_off = lseek(m_fd, 0, SEEK_END);
  assert(size_off >= 0);
  m_size = (size_t)size_off;
  m_ptr = mmap(nullptr, m_size, PROT_READ, MAP_PRIVATE, m_fd, 0);
}

MmapHandle::~MmapHandle()
{
  assert(0 == munmap(m_ptr, m_size));
  assert(0 == close(m_fd));
}

int MmapHandle::fd() const
{
  return m_fd;
}

size_t MmapHandle::size() const
{
  return m_size;
}

void* MmapHandle::ptr() const
{
  return m_ptr;
}
