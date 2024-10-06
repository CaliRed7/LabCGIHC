#pragma once
#include "Light.h"

class PointLight ://superclase
	public Light
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue,//colores
		GLfloat aIntensity, GLfloat dIntensity,//intensidad
		GLfloat xPos, GLfloat yPos, GLfloat zPos,//vector de posicion
		GLfloat con, GLfloat lin, GLfloat exp);//valores resultado de una ecuación de 2° grado ax2+bx+c

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientcolorLocation,
		GLfloat diffuseIntensityLocation, GLfloat positionLocation,
		GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation);

	~PointLight();

protected://variables de tipo protected por lo que classs pointlight tambien es una superclase
	glm::vec3 position;

	GLfloat constant, linear, exponent;
};

