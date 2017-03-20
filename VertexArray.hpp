// VertexArray.cpp
// Class that holds the vertex information in a VertexArray object

#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include <vector>
#include <map>
#include <string>

#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using std::vector;
using std::map;
using std::string;

class VertexArray {
    private:
        std::map<string,GLuint> buffers;
    public:
        GLuint id;
        unsigned int count;
      	int numFaces;
        float minX, minY, minZ, maxX, maxY, maxZ;
        glm::vec4 center;
        glm::vec3 size;

        VertexArray(int c, int numberOfFaces);
        void addBuffer(string name, int index, vector<float> buffer, int components);

        void addBoundingDimensions(float minX, float maxX,
                                   float minY, float maxY,
                                   float minZ, float maxZ);

        void updateBuffer(string name, vector<float> buffer);
        virtual ~VertexArray();
};

#endif // VERTEX_ARRAY_HPP
