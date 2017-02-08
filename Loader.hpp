// Loader.hpp
// Class that loads a .obj file into vectors of floats for OpenGL

#ifndef LOADER_HPP
#define LOADER_HPP

#include <vector>

#include <glm/glm.hpp>

using std::vector;

class Loader {

    private:

    public:
        static vector<float> loadObjFile(const char * path);
}
