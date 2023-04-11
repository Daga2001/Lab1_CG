#include "VectorMesh.h"

VectorMesh::VectorMesh() : Mesh()
{
	x = 1;
	y = 0;
	z = 0;
	origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

VectorMesh::VectorMesh(float xPos) : Mesh()
{
	x = xPos;
	y = 0;
	z = 0;
	origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

VectorMesh::VectorMesh(float xPos, float yPos) : Mesh()
{
	x = xPos;
	y = yPos;
	z = 0;
	origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

VectorMesh::VectorMesh(float xPos, float yPos, float zPos) : Mesh()
{
	x = xPos;
	y = yPos;
	z = zPos;
	origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

VectorMesh::VectorMesh(float xPos, float yPos, float zPos, glm::vec3 orig) : Mesh()
{
	x = xPos;
	y = yPos;
	z = zPos;
	origin = orig;
}

glm::vec3 VectorMesh::getCoordinates()
{
	return glm::vec3(x, y, z);
}

glm::vec3 VectorMesh::getOrigin()
{
	return origin;
}

void VectorMesh::drawVector()
{
	float ox = origin.x;
	float oy = origin.y;
	float oz = origin.z;

	unsigned int numOfVertices = 6;
	unsigned int numOfIndices = 2;
	unsigned int vectorindices[] = {
		0, 1,
	};
	GLfloat vectorVertices[] = {
	//	x		y		z
		ox,		oy,		oz,
		x,		y,		z,
	};

	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vectorindices[0]) * numOfIndices, vectorindices, GL_STATIC_DRAW);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vectorVertices[0]) * numOfVertices, vectorVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VectorMesh::renderVector()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	float res[2];
	glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

VectorMesh::~VectorMesh()
{
	ClearMesh();
}