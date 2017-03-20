// ErrorChecking.hpp
// A class for error checking code

#include <iostream>

using std::cout;
using std::endl;

class ErrorChecking {

  public:
    static void CheckGLErrors() {
      bool error = false;
      for (GLenum flag = glGetError(); flag != GL_NO_ERROR; flag = glGetError()) {
        cout << "OpenGL ERROR:  ";
        switch (flag) {
          case GL_INVALID_ENUM:
            cout << "GL_INVALID_ENUM" << endl; break;
          case GL_INVALID_VALUE:
            cout << "GL_INVALID_VALUE" << endl; break;
          case GL_INVALID_OPERATION:
            cout << "GL_INVALID_OPERATION" << endl; break;
          case GL_INVALID_FRAMEBUFFER_OPERATION:
            cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << endl; break;
          case GL_OUT_OF_MEMORY:
            cout << "GL_OUT_OF_MEMORY" << endl; break;
          default:
            cout << "[unknown error code]" << endl;
        }
        error = true;
      }
    }

};
