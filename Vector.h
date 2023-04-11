#pragma once
class Vector
{
public:
	Vector();
	Vector(float xPos);
	Vector(float xPos, float yPos);
	Vector(float xPos, float yPos, float zPos);

	int getXPosition();
	int getYPosition();
	int getZPosition();

	~Vector();

private:
	float xPosition;
	float yPosition;
	float zPosition;

};

