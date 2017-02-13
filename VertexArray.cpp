// VertexArray.cpp
// Class that holds the vertex information in a VertexArray object

#include "VertexArray.hpp"


VertexArray::VertexArray(int c) : count(c){
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

void VertexArray::addBoundingDimensions(float minX, float maxX,
                                        float minY, float maxY,
                                        float minZ, float maxZ) {
    this->minX = minX;
    this->minY = minY;
    this->minZ = minZ;
    this->maxX = maxX;
    this->maxY = maxY;
    this->maxZ = maxZ;
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
