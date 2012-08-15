#include <assert.h>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <SDL.h>
#include <GL/glew.h>

#include "client/view/shader.h"

Shader::Shader(const char* vertex_file, const char* fragment_file)
{
  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

  LoadShader(vertex_file, fragment_file);
}

Shader::~Shader() {
  glDeleteProgram(shader_program);
  glDeleteShader(fragment_shader);
  glDeleteShader(vertex_shader);
  glDeleteBuffers(1, &vertex_buffer);
  glDeleteVertexArrays(1, &vertex_array);
}

void Shader::On() const {
  glUseProgram(shader_program);
  glBindVertexArray(vertex_array);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
}

size_t Shader::MmapFile(const char* filename, int* fd, void** p) {
  *fd = open(filename, 0, O_RDONLY);
  assert(*fd >= 0);
  off_t size_off = lseek(*fd, 0, SEEK_END);
  assert(size_off > 0);
  size_t size = (size_t)size_off;
  *p = mmap(nullptr, size, PROT_READ, MAP_PRIVATE, *fd, 0);
  return size;
}

void Shader::UnmmapFile(size_t size, int fd, void* p) {
  assert(0 == munmap(p, size));
  assert(0 == close(fd));
}

GLuint Shader::AddShaderSource(const char* filename, int type) {
  int fd;
  const char *s = nullptr;
  assert(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER);

  GLuint shader = glCreateShader(type);
  size_t size = MmapFile(filename, &fd, (void**)&s);
  glShaderSource(shader, 1, &s, nullptr);
  UnmmapFile(size, fd, (void*)s);
  return shader;
}

void Shader::LoadShader(const char* vertexFile, const char* fragFile)
{
  GLint status;

  vertex_shader = AddShaderSource(vertexFile, GL_VERTEX_SHADER);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
  std::cout << "vertex shader " << vertexFile << ": " << status << std::endl;
  if (status != 1) {
    char buffer[513];
    glGetShaderInfoLog(vertex_shader, 512, NULL, buffer );
    std::cout << buffer << std::endl;
    exit(1);
  }

  fragment_shader = AddShaderSource(fragFile, GL_FRAGMENT_SHADER);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status );
  std::cout << "fragment shader " << fragFile << ": " << status << std::endl;
  if (status != 1) {
    char buffer[513];
    glGetShaderInfoLog(fragment_shader, 512, NULL, buffer );
    std::cout << buffer << std::endl;
    exit(1);
  }

  shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);
}

