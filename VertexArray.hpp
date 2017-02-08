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

using std::vector;
using std::map;
using std::string;

class VertexArray {
    private:
        std::map<string,GLuint> buffers;
    public:
        GLuint id;
        unsigned int count;


        VertexArray(int c);
        void addBuffer(string name, int index, vector<float> buffer);

        void updateBuffer(string name, vector<float> buffer);
        virtual ~VertexArray();
};

#endif // VERTEX_ARRAY_HPP
