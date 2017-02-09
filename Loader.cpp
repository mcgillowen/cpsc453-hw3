// Loader.cpp
// Class that loads a .obj file into vectors of floats for OpenGL

#include <vector>
#include <cstdio>
#include <cstring>

#include "Loader.hpp"

using std::vector;
using std::fscanf;
using std::strcmp;
using std::printf;
using namespace glm;


IndexedVertexArray Loader::loadObjFile(const char * path) {

    vector<float> vertices;
    vector<unsigned int> vertexIndices;
    vector<float> normals;

    int numVertices = 0;

    bool openFile = true;

    FILE * file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file \n");
        openFile = false;
    }

    while (openFile) {

        char lineType[5];
        int res= fscanf(file, "%s", lineType);

        if (res == EOF) {
            break;
        }

        if (strcmp(lineType, "v") == 0) {
            vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            numVertices++;
            vertices.push_back(vertex.x);
            vertices.push_back(vertex.y);
            vertices.push_back(vertex.z);
        } else if (strcmp(lineType, "f") == 0) {
            unsigned int vertexIndex[3];
            int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0],
             &vertexIndex[1], &vertexIndex[2]);

            if (matches != 3) {
                printf("There was not the expected number of indexes");
                openFile = false;
                break;
            }

            vec3 v0 = vertices.at(vertexIndex[0]);
            vec3 v1 = vertices.at(vertexIndex[1]);
            vec3 v2 = vertices.at(vertexIndex[2]);

            vec3 edge1 = v1 - v0;
            vec3 edge2 = v2 - v0;

            vec3 normal = cross(edge1, edge2);
            normal = normalize(normal);

            normals.push_back(normal.x);
            normals.push_back(normal.y);
            normals.push_back(normal.z);

            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
        }
    }

    IndexedVertexArray* va = new IndexedVertexArray(numVertices);

    va->addBuffer("vertices", 0, vertices);
    va->addBuffer("normals", 1, normals);

    va->addIndexBuffer(vertexIndices);

    return va;
}
