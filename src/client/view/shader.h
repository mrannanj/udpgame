#pragma once

#include <string>

#include "common/platform.h"
#include "common/resource_locator.h"

class Shader {
public:
  Shader(const ResourceLocator&, const std::string&, const std::string&);
  virtual ~Shader();

  virtual void On() const;

protected:
  ResourceLocator mResourceLocator;
  GLuint vertex_buffer;
  GLuint vertex_shader;
  GLuint fragment_shader;
  GLuint shader_program;

private:
  void LoadShader(const char*, const char*);
  GLuint AddShaderSource(const char*, int);
  size_t MmapFile(const char*, int*, void**);
  void UnmmapFile(size_t, int, void*);
};
