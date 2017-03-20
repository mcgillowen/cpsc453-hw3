// Texture.hpp
// Class that loads a Texture file into OpenGL

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include "ErrorChecking.hpp"

class Texture {
public:
  GLuint target; // GL_TEXTURE_2D/GL_TEXTURE_RECTANGLE/...
  GLuint id;
  int width;
  int height;
  Texture();
  Texture(std::string filename, GLuint target = GL_TEXTURE_2D);
  void init(std::string filename, GLuint target = GL_TEXTURE_2D);
  ~Texture();
};

#endif // TEXTURE_HPP
