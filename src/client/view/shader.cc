
#include <SDL.h>
#include <GL/glew.h>
#include <cassert>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "client/view/shader.h"
#include "common/util/mmap_handle.h"
#include "common/resource_locator.h"

using namespace std;

Shader::Shader(const ResourceLocator& resourceLocator,
    const string& vertex_file, const string& fragment_file):
  mResourceLocator(resourceLocator),
  vertex_array(),
  vertex_buffer(),
  vertex_shader(),
  fragment_shader(),
  shader_program()
{
  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

  for (const std::string& prefix : mResourceLocator.pathPrefix()) {
    std::stringstream vertexPath;
    vertexPath << prefix << "/" << vertex_file;
    if (-1 == access(vertexPath.str().c_str(), F_OK | R_OK))
      continue;

    std::stringstream fragmentPath;
    fragmentPath << prefix << "/" << fragment_file;
    if (-1 == access(fragmentPath.str().c_str(), F_OK | R_OK))
      continue;

    LoadShader(vertexPath.str().c_str(), fragmentPath.str().c_str());
    return;
  }
  std::cerr << "Failed to load " << vertex_file << " or " << fragment_file
    << std::endl;
  exit(EXIT_FAILURE);
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

GLuint Shader::AddShaderSource(const char* filename, int type) {
  assert(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER);

  GLuint shader = glCreateShader(type);
  MmapHandle f(filename);
  const char* p = (const char*) f.ptr();
  glShaderSource(shader, 1, &p, nullptr);
  return shader;
}

void Shader::LoadShader(const char* vertexFile, const char* fragFile) {
  GLint status;

  vertex_shader = AddShaderSource(vertexFile, GL_VERTEX_SHADER);
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
  if (status != 1) {
    std::cout << "vertex shader " << vertexFile << ": " << status << std::endl;
    char buffer[513];
    glGetShaderInfoLog(vertex_shader, 512, NULL, buffer );
    std::cout << buffer << std::endl;
    exit(1);
  }

  fragment_shader = AddShaderSource(fragFile, GL_FRAGMENT_SHADER);
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &status );
  if (status != 1) {
    std::cout << "fragment shader " << fragFile << ": " << status << std::endl;
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

