// Loader.hpp
// Class that loads a .obj file into vectors of floats for OpenGL

#ifndef LOADER_HPP
#define LOADER_HPP

#include <vector>
#include <cstdio>
#include <cstring>
#include "VertexArray.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using std::vector;

class Loader {

    private:

    public:
        float minX, minY, minZ, maxX, maxY, maxZ;
        VertexArray* loadObjFile(const char * path);
};

#endif // LOADER_HPP
