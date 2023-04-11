#pragma once
#include <glm.hpp>

class MathOGL
{
public:
	MathOGL();
	glm::vec3 vecSum(glm::vec3 vec1, glm::vec3 vec2);
	glm::vec3 vectorSubtraction(glm::vec3 vec1, glm::vec3 vec2);
	glm::vec3 scalarMultiplication(glm::vec3 vec1, double escalar);
	glm::vec3 crossProduct(glm::vec3 vec1, glm::vec3 vec2);
	double dotProduct(glm::vec3 vec1, glm::vec3 vec2);
	glm::vec3 scalarDivision(glm::vec3 vec1, double escalar);
	double angleBetween(glm::vec3 vec1, glm::vec3 vec2);
	glm::vec3 normalize(glm::vec3 vec1);
	glm::mat4 translate(glm::vec3 t);


	~MathOGL();
};

