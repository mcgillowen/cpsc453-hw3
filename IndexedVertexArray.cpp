// IndexedVertexArray.hpp
// A class holding a Indexed Vertex Array, sub class of VertexArray

#include "IndexedVertexArray.hpp"

IndexedVertexArray::IndexedVertexArray( int c ) : VertexArray( c ), elementbuffer(0) {
}

void IndexedVertexArray::addIndexBuffer( vector<unsigned int> indices ) {
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexedVertexArray::~IndexedVertexArray() {
    // do proper cleanup.
}
