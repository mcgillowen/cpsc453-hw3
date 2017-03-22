// Texture.cpp
// Class that loads a Texture file into OpenGL

#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using std::cout;
using std::endl;

Texture::Texture() {}

Texture::Texture(std::string filename, Program& p, GLuint target) {
  init(filename, p, target);
}

void Texture::init(std::string filename, Program& p, GLuint target) {
  int numComponents;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(filename.c_str(), &width, &height, &numComponents, 0);
  if (data != nullptr)
  {
    this->target = target;
    cout << "24" << endl;
    ErrorChecking::CheckGLErrors();
    glGenTextures(1, &id);
    cout << "26" << endl;
    ErrorChecking::CheckGLErrors();
    glBindTexture(target, id);
    cout << "29" << endl;
    ErrorChecking::CheckGLErrors();
    GLuint formats[] = {GL_RED,GL_RG,GL_RGB,GL_RGBA};
    GLuint format = formats[numComponents-1];

    cout << numComponents << ", " << format << ", " << GL_RGB << endl;
    cout << target << ", " << GL_TEXTURE_2D << endl;

    cout << "width:" << width << endl;
    cout << "height:" << height << endl;

    glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    cout << "38" << endl;
    ErrorChecking::CheckGLErrors();
    //glActiveTexture(GL_TEXTURE0);
    cout << "41" << endl;
    ErrorChecking::CheckGLErrors();
    //glEnable(GL_TEXTURE_2D); // Enable it
    cout << "44" << endl;
    ErrorChecking::CheckGLErrors();

    glBindTexture(target, id);
    cout << "48" << endl;
    ErrorChecking::CheckGLErrors();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);


    //GLuint hTexture = glGetUniformLocation(p.id, "texSam");
    cout << "59" << endl;
    ErrorChecking::CheckGLErrors();
    //glUniform1i(hTexture, 0);
    cout << "62" << endl;
    ErrorChecking::CheckGLErrors();


    //glBindTexture(target, 0);
    stbi_image_free(data);
    cout << "68" << endl;
    ErrorChecking::CheckGLErrors();
  }
}

Texture::~Texture() {
  // glBindTexture(target, 0);
  // glDeleteTextures(1, &id);
}
