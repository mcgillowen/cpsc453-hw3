// VertexArray.cpp
// Class that holds the vertex information in a VertexArray object

#include "VertexArray.hpp"


VertexArray::VertexArray(int c, int numberOfFaces) : count(c), numFaces(numberOfFaces){
    glGenVertexArrays(1, &id);
}

void VertexArray::addBuffer(string name, int index, vector<float> buffer) {
    GLuint buffer_id;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, buffer.size()*sizeof(float), buffer.data(), GL_STATIC_DRAW);
    buffers[name]=buffer_id;

    int components=buffer.size()/count;
    glBindVertexArray(id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, components, GL_FLOAT, GL_FALSE, 0, 0);


    // unset states
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VertexArray::addBoundingDimensions(float min_X, float max_X,
                                        float min_Y, float max_Y,
                                        float min_Z, float max_Z) {
    minX = min_X;
    minY = min_Y;
    minZ = min_Z;
    maxX = max_X;
    maxY = max_Y;
    maxZ = max_Z;

    center = glm::vec4((maxX - minX)/2.0, (maxY - minY)/2.0, (maxZ - minZ)/2.0, 1.0);
    size = glm::vec3(maxX - minX, maxY - minY, maxZ - minZ);
}

void VertexArray::updateBuffer(string name, vector<float> buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, buffers[name]);
    glBufferData(GL_ARRAY_BUFFER, buffer.size()*sizeof(float), buffer.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexArray::~VertexArray() {
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    for(auto &ent: buffers)
        glDeleteBuffers(1, &ent.second);
}
