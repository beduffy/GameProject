#pragma once

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

class SpotLight {
public:
	SpotLight(glm::vec3 dir, glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, 
			  GLfloat linear, GLfloat quadratic, GLfloat cutOff, GLfloat outerCutOff) :
		direction(dir),
		position(pos),
		ambient(ambient),
		diffuse(diffuse),
		specular(specular),
		linear(linear),
		quadratic(quadratic),
		cutOff (cutOff), 
		outerCutOff(outerCutOff) {}

	glm::vec3 direction;
	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	GLfloat constant = 1.0f;
	GLfloat linear;
	GLfloat quadratic;

	GLfloat cutOff;
	GLfloat outerCutOff;
private:
};