// Loader.cpp
// Class that loads a .obj file into vectors of floats for OpenGL

#include "Loader.hpp"
#include "ErrorChecking.hpp"
#include <iostream>

using std::vector;
using std::fscanf;
using std::strcmp;
using std::printf;
using std::cout;
using std::endl;
using namespace glm;


VertexArray* Loader::loadObjFile(const char * path) {

    vector<float> vertices;
    vector<float> texVertices;
    vector<unsigned int> vertexIndices;
    vector<unsigned int> texIndices;
    vector<float> normals;

    vector<vec4> tempVertices;
    vector<vec2> tempTexVertices;
    vector<vec3> tempNormals;

    int numVertices = 0;
    int numTexVertices = 0;
    int numFaces = 0;

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
            tempVertices.push_back(vec4(vertex, 1.0));
            tempNormals.push_back(vec3(0.0,0.0,0.0));
        } else if (strcmp(lineType, "vt") == 0) {
            vec2 vertexTexture;
            fscanf(file, "%f %f\n", &vertexTexture.x, &vertexTexture.y);
            numTexVertices++;
            tempTexVertices.push_back(vertexTexture);
        } else if (strcmp(lineType, "f") == 0) {
            unsigned int vertexIndex[3];
            unsigned int textureIndex[3];
            int matches = fscanf(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &textureIndex[0],
             &vertexIndex[1], &textureIndex[1], &vertexIndex[2], &textureIndex[2]);

            if (matches != 6) {
                printf("There was not the expected number of indexes");
                openFile = false;
                break;
            }

            vertexIndices.push_back(vertexIndex[0] - 1);
            vertexIndices.push_back(vertexIndex[1] - 1);
            vertexIndices.push_back(vertexIndex[2] - 1);

            texIndices.push_back(textureIndex[0] - 1);
            texIndices.push_back(textureIndex[1] - 1);
            texIndices.push_back(textureIndex[2] - 1);

            numFaces++;
        }
    }

    tempNormals.resize(tempVertices.size(), vec3(0.0, 0.0, 0.0));
    for (int i = 0; i < vertexIndices.size(); i += 3) {
      unsigned int indexA = vertexIndices[i];
      unsigned int indexB = vertexIndices[i + 1];
      unsigned int indexC = vertexIndices[i + 2];

      vec3 normal = normalize(cross(
        vec3(tempVertices[indexB]) - vec3(tempVertices[indexA]),
        vec3(tempVertices[indexC]) - vec3(tempVertices[indexA])
      ));

      tempNormals[indexA] += normal;
      tempNormals[indexB] += normal;
      tempNormals[indexC] += normal;
    }

    for (int i = 0; i < vertexIndices.size(); i++) {
      unsigned int vertexIndex = vertexIndices[i];
      unsigned int textureIndex = texIndices[i];

      vec4 vertex = tempVertices[vertexIndex];
      vec2 texture = tempTexVertices[textureIndex];
      vec3 normal = normalize(tempNormals[vertexIndex]);

      vertices.push_back(vertex.x);
      vertices.push_back(vertex.y);
      vertices.push_back(vertex.z);
      vertices.push_back(vertex.w);

      texVertices.push_back(texture.x);
      texVertices.push_back(texture.y);

      normals.push_back(normal.x);
      normals.push_back(normal.y);
      normals.push_back(normal.z);
    }

    float minX, minY, minZ, maxX, maxY, maxZ;

    minX = tempVertices[0].x;
    maxX = tempVertices[0].x;
    minY = tempVertices[0].y;
    maxY = tempVertices[0].y;
    minZ = tempVertices[0].z;
    maxZ = tempVertices[0].z;

    for (int i = 1; i < tempVertices.size(); i++) {
      if (tempVertices[i].x < minX) minX = tempVertices[i].x;
      if (tempVertices[i].x > maxX) maxX = tempVertices[i].x;
      if (tempVertices[i].y < minY) minY = tempVertices[i].y;
      if (tempVertices[i].y > maxY) maxY = tempVertices[i].y;
      if (tempVertices[i].z < minZ) minZ = tempVertices[i].z;
      if (tempVertices[i].z > maxZ) maxZ = tempVertices[i].z;
    }

    VertexArray* va = new VertexArray(numVertices, numFaces);

    va->addBuffer("vertices", 0, vertices, 4);
    va->addBuffer("normals", 1, normals, 3);
    va->addBuffer("textures", 2, texVertices, 2);
    va->addBoundingDimensions(minX, minY, minZ, maxX, maxY, maxZ);

    return va;
}
