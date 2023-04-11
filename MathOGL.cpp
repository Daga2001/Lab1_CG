#include "MathOGL.h"

MathOGL::MathOGL()
{

}

glm::vec3 MathOGL::vecSum(glm::vec3 vec1, glm::vec3 vec2)
{
	return glm::vec3(
		vec1.x + vec2.x,
		vec1.y + vec2.y,
		vec1.z + vec2.z
	);
}

glm::vec3 MathOGL::vectorSubtraction(glm::vec3 vec1, glm::vec3 vec2)
{
	return glm::vec3(
		vec1.x - vec2.x,
		vec1.y - vec2.y,
		vec1.z - vec2.z
	);
}

glm::vec3 MathOGL::scalarMultiplication(glm::vec3 vec1, double escalar)
{
	return glm::vec3(
		vec1.x * escalar,
		vec1.y * escalar,
		vec1.z * escalar
	);
}

glm::vec3 MathOGL::crossProduct(glm::vec3 vec1, glm::vec3 vec2)
{
	return glm::vec3(
		vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x
	);
}

double MathOGL::dotProduct(glm::vec3 vec1, glm::vec3 vec2)
{
	return
		(double)(vec1.x) * (double)(vec2.x) +
		(double)(vec1.y) * (double)(vec2.y) +
		(double)(vec1.z) * (double)(vec2.z);
}

glm::vec3 MathOGL::scalarDivision(glm::vec3 vec1, double escalar)
{
	return glm::vec3(
		vec1.x / escalar,
		vec1.y / escalar,
		vec1.z / escalar
	);
}

double MathOGL::angleBetween(glm::vec3 vec1, glm::vec3 vec2)
{
	double dotp = dotProduct(vec1, vec2);
	double len1 = sqrt(dotProduct(vec1, vec1));
	double len2 = sqrt(dotProduct(vec2, vec2));
	double cosTheta = dotp / (len1 * len2);
	return acos(cosTheta);
}

glm::vec3 MathOGL::normalize(glm::vec3 vec1)
{
	double len1 = sqrt(dotProduct(vec1, vec1));
	return scalarDivision(vec1, len1);
}

glm::mat4 MathOGL::translate(glm::vec3 t) {
	glm::mat4 result(1.0f);
	result[3] = glm::vec4(t, 1.0f);
	return result;
}

MathOGL::~MathOGL()
{

}