#include <assert.h>
#include <assert.h>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <SDL.h>
#include <GL/glew.h>

#include "client/view/shader_loader.h"

size_t mmap_file(const char* filename, int* fd, void** p) {
  *fd = open(filename, 0, O_RDONLY);
  assert(*fd >= 0);
  off_t size_off = lseek(*fd, 0, SEEK_END);
  assert(size_off > 0);
  size_t size = (size_t)size_off;
  *p = mmap(nullptr, size, PROT_READ, MAP_PRIVATE, *fd, 0);
  return size;
}

void unmmap_file(size_t size, int fd, void* p) {
  assert(0 == munmap(p, size));
  assert(0 == close(fd));
}

GLuint AddShaderSource(const char* filename, int type) {
  int fd;
  const char *s = nullptr;
  assert(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER);

  GLuint shader = glCreateShader(type);
  size_t size = mmap_file(filename, &fd, (void**)&s);
  glShaderSource(shader, 1, &s, nullptr);
  unmmap_file(size, fd, (void*)s);
  return shader;
}

GLuint LoadShaders(const char* vertexFile, const char* fragFile,
  GLuint* vert, GLuint* frag)
{
  GLint status;

  *vert = AddShaderSource(vertexFile, GL_VERTEX_SHADER);
  glCompileShader(*vert);
  glGetShaderiv(*vert, GL_COMPILE_STATUS, &status);
  std::cout << "vertex shader " << vertexFile << ": " << status << std::endl;
  if (status != 1) {
    char buffer[513];
    glGetShaderInfoLog(*vert, 512, NULL, buffer );
    std::cout << buffer << std::endl;
    exit(1);
  }

  *frag = AddShaderSource(fragFile, GL_FRAGMENT_SHADER);
  glCompileShader(*frag);
  glGetShaderiv(*frag, GL_COMPILE_STATUS, &status );
  std::cout << "fragment shader " << fragFile << ": " << status << std::endl;
  if (status != 1) {
    char buffer[513];
    glGetShaderInfoLog(*frag, 512, NULL, buffer );
    std::cout << buffer << std::endl;
    exit(1);
  }

  GLuint prog = glCreateProgram();
  glAttachShader(prog, *vert);
  glAttachShader(prog, *frag);
  glBindFragDataLocation(prog, 0, "outColor");
  glLinkProgram(prog);
  glUseProgram(prog);

  return prog;
}

