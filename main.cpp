#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "VectorMesh.h"
#include "Shader.h"
#include "Camera.h"
#include "MathOGL.h"

const float toRadians = 3.14159265f / 180.0f;
const float nearPlane = 0.1f;
const float farPlane = 100.0f;
const float deltaPlane = glm::abs(farPlane - nearPlane);
const glm::vec3 windowColor = glm::vec3(153, 75, 214);

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<VectorMesh*> vectorMeshList;
std::vector<Shader> shaderList;
Camera camera;
MathOGL mathGL = MathOGL();

//------------------------------------------------------------------------------------------------------------
// physics variables
//------------------------------------------------------------------------------------------------------------
// Parabolic movement
//------------------------------------------------------------------------------------------------------------
double velocity = 10.0f;
const double gravity = 9.81f;
double height = 30.0f;
double angle = 79.5f;
double tim = 0.0f;
double angleRadians = angle * toRadians;
double xPos = 0.0f;
double yPos = height;
double zPos = 0.0f;
double velX = velocity * glm::cos(angleRadians);
double velY = velocity * glm::sin(angleRadians);
//------------------------------------------------------------------------------------------------------------
// Bullet movement
//------------------------------------------------------------------------------------------------------------
bool xDir = true;
double xPos1D = 0.0f;
double xIncrement = 0.01f;
double xMax = 10.0f;
//------------------------------------------------------------------------------------------------------------
// rotation 
//------------------------------------------------------------------------------------------------------------
float rotDegrees = 0.0f;
float maxRotation = 0.0f;
//------------------------------------------------------------------------------------------------------------

GLfloat cubeW = 1.0f;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void testPool()
{
	glm::vec3 vec1 = glm::vec3(1.0, 2.0, 3.0);
	glm::vec3 vec2 = glm::vec3(1.0, 2.0, 5.0);
	double escalar = 5.0f;
	double dotp = mathGL.dotProduct(vec1, vec2);
	double theta = mathGL.angleBetween(vec1, vec2);
	glm::vec3 crossp = mathGL.crossProduct(vec1, vec2);
	glm::vec3 normV1 = mathGL.normalize(vec1);
	glm::vec3 scalard = mathGL.scalarDivision(vec1, escalar);
	glm::vec3 scalarm = mathGL.scalarMultiplication(vec1, escalar);
	glm::vec3 vecSm =mathGL.vecSum(vec1, vec2);
	glm::vec3 vecSub = mathGL.vectorSubtraction(vec1, vec2);	
	printf("vec1: (%f,%f,%f), vec2: (%f,%f,%f)\n", vec1.x, vec1.y, vec1.z, vec2.x, vec2.y, vec2.z);
	printf("dot Product: %f\n", dotp);
	printf("angle between: %f\n", theta);
	printf("cross Product: (%f,%f,%f)\n", crossp.x, crossp.y, crossp.z);
	printf("normalized v1: (%f,%f,%f)\n", normV1.x, normV1.y, normV1.z);
	printf("scalar multiplication: (%f,%f,%f)\n", scalarm.x, scalarm.y, scalarm.z);
	printf("scalar division: (%f,%f,%f)\n", scalard.x, scalard.y, scalard.z);
	printf("Vec sum: (%f,%f,%f)\n", vecSm.x, vecSm.y, vecSm.z);
	printf("Vec subtraction: (%f,%f,%f)\n", vecSub.x, vecSub.y, vecSub.z);
	double lenCrossp = sqrt(mathGL.dotProduct(crossp, crossp));
	double lenV1 = sqrt(mathGL.dotProduct(vec1, vec1));
	double lenV2 = sqrt(mathGL.dotProduct(vec2, vec2));
	double property = lenV1 * lenV2 * sin(theta);
	printf("lenCrossp: %f, property: %f\n", lenCrossp, property);
}

void processParabolicMove1D()
{
	if (xDir)
	{
		xPos1D += xIncrement;
	}
	else
	{
		xPos1D -= xIncrement;
	}

	if (abs(xPos1D) > xMax)
	{
		xDir = !xDir;
	}
}

void processParabolicMove()
{
	xPos = velX * tim;
	yPos = velY * tim - (gravity / 2) * glm::pow(tim, 2.0f);
	zPos = 0;

	//printf("x: %f, y:%f, z: %f, time: %f\n", xPos, yPos, zPos, tim);

	tim += deltaTime;

	if (yPos < 0)
	{
		xPos = 0.0f;
		yPos = height;
		zPos = 0.0f;
		tim = 0;
	}
}

void rotationMove()
{
	rotDegrees += deltaTime;
	if (rotDegrees >= 360)
	{
		rotDegrees -= 360;
	}
}

void printMatrix(glm::mat4 matrix) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void CreateObjects() 
{
	unsigned int surfaceIndices[] = {
		0, 2, 3,
		0, 3, 1,
	};

	GLfloat surfaceVertices[] = {
		// x		y			z
		-deltaPlane, 0.0f, deltaPlane,
		deltaPlane, 0.0f, deltaPlane,
		-deltaPlane, 0.0f, -deltaPlane,
		deltaPlane, 0.0f, -deltaPlane,
	};

	unsigned int cubeIndices[] = {
		//top face
		0, 1, 2,
		1, 2, 3,
		//bottom face
		4, 5, 6,
		5, 6, 7,
		//left face
		4, 0, 6,
		0, 2, 6,
		//right face
		5, 7, 3,
		5, 1, 3,
		//front face
		6, 7, 2, 
		2, 3, 7,
		//back face
		4, 5, 0,
		0, 1, 5,
	};

	GLfloat cubeVertices[] = {
		0.0f, cubeW, 0.0f,
		cubeW, cubeW, 0.0f,
		0.0f, cubeW, cubeW,
		cubeW, cubeW, cubeW,						
		0.0f, 0.0f, 0.0f,
		cubeW, 0.0f, 0.0f,
		0.0f, 0.0f, cubeW,
		cubeW, 0.0f, cubeW,
	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(surfaceVertices, surfaceIndices, 24, 6);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(cubeVertices, cubeIndices, 24, 36);
	meshList.push_back(obj2);

	//makes a X-axis in cartesian plane
	VectorMesh* obj3 = new VectorMesh(deltaPlane, 0.0f, 0.0f, glm::vec3(-deltaPlane, 0.0f, 0.0f));
	obj3->drawVector();
	vectorMeshList.push_back(obj3);

	//makes a Y-axis in cartesian plane
	VectorMesh* obj4 = new VectorMesh(0.0f, deltaPlane, 0.0f, glm::vec3(0.0f, -deltaPlane, 0.0f));
	obj4->drawVector();
	vectorMeshList.push_back(obj4);

	//makes a Z-axis in cartesian plane
	VectorMesh* obj5 = new VectorMesh(0.0f, 0.0f, deltaPlane, glm::vec3(0.0f, 0.0f, -deltaPlane));
	obj5->drawVector();
	vectorMeshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(cubeVertices, cubeIndices, 24, 36);
	meshList.push_back(obj6);

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(cubeVertices, cubeIndices, 24, 36);
	meshList.push_back(obj7);
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main() 
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	testPool();

	camera = Camera(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), -140.0f, -40.0f, 5.0f, 0.5f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity = 0, uniformAmbientColour = 0;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), nearPlane, farPlane);

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/ SDL_GetPerformaceFrequency()
		lastTime = now;

		// Get + Handle User Input
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(windowColor.x/256, windowColor.y/256, windowColor.z/256, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
		uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();

		glm::mat4 model(1.0f);		

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		meshList[0]->RenderMesh();

		processParabolicMove();
		rotationMove();

		glm::mat4 test(1.0f);
		test = glm::mat4(1.0f);
		test = mathGL.translate(glm::vec3(xPos, yPos, zPos));
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(xPos, yPos, zPos));
		model = glm::rotate(model, rotDegrees, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		vectorMeshList[0]->renderVector();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		vectorMeshList[1]->renderVector();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		vectorMeshList[2]->renderVector();

		processParabolicMove1D();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, xPos1D));
		model = glm::rotate(model, rotDegrees, glm::vec3(1.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-xPos, yPos, xPos));
		model = glm::rotate(model, rotDegrees, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[3]->RenderMesh();

		glUseProgram(0);
			
		mainWindow.swapBuffers();
	}

	return 0;
}