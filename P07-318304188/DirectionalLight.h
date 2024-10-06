#pragma once
#include "Light.h"

class DirectionalLight : //recibe los 6 valores de la clase light
	public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
					GLfloat aIntensity, GLfloat dIntensity,
					GLfloat xDir, GLfloat yDir, GLfloat zDir);//desde donde ilumnia

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientcolorLocation,//setea lasvariables para enviarselas al shader
		GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	~DirectionalLight();

private://variable privada de su vector de dirección
	glm::vec3 direction;
};

