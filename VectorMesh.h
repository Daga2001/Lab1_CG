#pragma once
#include "Mesh.h"
#include <glm.hpp>

class VectorMesh:
    public Mesh
{
public:
    VectorMesh();
    VectorMesh(float xPos);
    VectorMesh(float xPos, float yPos);
    VectorMesh(float xPos, float yPos, float zPos);
    VectorMesh(float xPos, float yPos, float zPos, glm::vec3 orig);
    glm::vec3 getCoordinates();
    glm::vec3 getOrigin();
    void drawVector();
    void renderVector();
    ~VectorMesh();

private:
    float x;
    float y;
    float z;
    glm::vec3 origin;
};

