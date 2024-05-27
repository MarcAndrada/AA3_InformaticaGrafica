#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat _red, GLfloat _green, GLfloat _blue, GLfloat _ambientIntensity);

	glm::vec3 color;
	GLfloat ambientIntensity;
};

