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


vector<float> Loader::loadObjFile(const char * path) {

    vector<glm::vec3> vertices;
    vector<unsigned int> vertexIndices;
    vector<glm::vec3> normals;

    FILE * file = fopen(path, r);
    if (file == NULL) {
        printf("Impossible to open the file \n");
        return false;
    }

    while (true) {

        char lineType[5];
        int res= fscanf(file, "%s", lineType);

        if (res == EOF) {
            break;
        }

        if (strcmp(lineType, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            vertices.push_back(vertex);
            normals.push_back(vertex);
        } else if (strcmp(lineType, "f") == 0) {
            unsigned int vertexIndex[3];
            int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);

            if (matches != 3) {
                printf("There was not the expected number of indexes");
                return false;
            }

            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
        }
    }
}
