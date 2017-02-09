// Program.hpp
// A class for OpenGL programs

#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

using std::string;
using std::endl;
using std::cerr;

class Program {
  GLuint vertex_shader;
  GLuint fragment_shader;
public:
  GLuint id;
  Program();
  Program(string vertex_path, string fragment_path);
  void init(string vertex_path, string fragment_path);
  GLuint addShader(string path, GLuint type);
  ~Program();
};

#endif //PROGRAM_HPP
