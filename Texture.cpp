// Texture.cpp
// Class that loads a Texture file into OpenGL

#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using std::cout;
using std::endl;

Texture::Texture() {}

Texture::Texture(std::string filename, GLuint target) {
  init(filename, target);
}

void Texture::init(std::string filename, GLuint target) {
  int numComponents;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(filename.c_str(), &width, &height, &numComponents, 0);
  if (data != nullptr)
  {
    this->target = target;
    glGenTextures(1, &id);

    glBindTexture(target, id);

    GLuint formats[] = {GL_RED,GL_RG,GL_RGB,GL_RGBA};
    GLuint format = formats[numComponents-1];

    cout << "width:" << width << endl;
    cout << "height:" << height << endl;

    glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    ErrorChecking::CheckGLErrors();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(target, 0);
    stbi_image_free(data);

    ErrorChecking::CheckGLErrors();
  }
}

Texture::~Texture() {
  // glBindTexture(target, 0);
  // glDeleteTextures(1, &id);
}


