#pragma once

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

class PointLight {
public:
	PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, GLfloat linear, GLfloat quadratic) :
		position(pos),
		ambient(amb),
		diffuse(diff),
		specular(spec),
		linear(linear), 
		quadratic(quadratic) {}

	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	GLfloat constant = 1.0f;
	GLfloat linear;
	GLfloat quadratic;
private:
};