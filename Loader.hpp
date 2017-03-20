// Loader.hpp
// Class that loads a .obj file into vectors of floats for OpenGL

#ifndef LOADER_HPP
#define LOADER_HPP

#include <vector>
#include <cstdio>
#include <cstring>
#include "IndexedVertexArray.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using std::vector;

class Loader {

    private:

    public:
        static VertexArray* loadObjFile(const char * path);
};

#endif // LOADER_HPP
