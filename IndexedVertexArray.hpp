// IndexedVertexArray.hpp
// A class holding a Indexed Vertex Array, sub class of VertexArray

#ifndef INDEXED_VERTEX_ARRAY_HPP
#define INDEXED_VERTEX_ARRAY_HPP

#include <vector>

#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

class IndexedVertexArray : public VertexArray {
public:
	GLuint elementbuffer;

	IndexedVertexArray( int c );

	void addIndexBuffer( vector<unsigned int> indices );

	virtual ~IndexedVertexArray();

};
