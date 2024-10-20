#pragma once

#include <glew.h>
#include <glm.hpp>

class Light//clase padre/super clase porque los 3 tipos de luuces tienen un color, una intensidad ambiental y una intensidad difusa
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, 
			GLfloat aIntensity, GLfloat dIntensity);//intensidad ambiental e intensidad difusa

	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

